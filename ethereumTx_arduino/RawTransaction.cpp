#include "RawTransaction.h"
#include "Tx.h"
#include "RLP.h"
#include "RpcRequest.h"
#include "env.h"
#include <keccak.h>
#include <secp256k1_recovery.h>


String createRawTransaction(String data, String privateKey) {
  String nonce = getNonce(WALLET_ADDRESS);
  Serial.print("Nonce: ");
  Serial.println(nonce);
  
  String gasLimit = getGasLimit();
  Serial.print("Gas Limit: ");
  Serial.println(gasLimit);

  Tx tx = {nonce, "0x", gasLimit, CONTRACT_ADDRESS, "0x", data, String(CHAIN_ID, HEX), "0x", "0x"};
  
  String txEncoded = rlpEncodeTx(&tx);
  String keccakHash = generateKeccakHash(txEncoded);
  return ecdsaSignature(keccakHash, privateKey, &tx);
}


String ecdsaSignature(String hash, String privateKey, Tx* tx) {
  uint8_t _hash[32];
  stringToUint(hash, _hash);
  uint8_t _privateKey[32];
  stringToUint(privateKey, _privateKey);

  secp256k1_context *ctx = NULL;
  int res;

  ctx = secp256k1_context_create(SECP256K1_CONTEXT_VERIFY | SECP256K1_CONTEXT_SIGN);

  secp256k1_ecdsa_recoverable_signature recoverySig;
  secp256k1_ecdsa_sign_recoverable(ctx, &recoverySig, _hash, _privateKey, NULL, NULL);

  int recid;
  unsigned char serialized_signature[64];
  
  secp256k1_ecdsa_recoverable_signature_serialize_compact(ctx, serialized_signature, &recid, &recoverySig);

  int _v = CHAIN_ID * 2 + 35 + recid;
  
  String r = find_r(serialized_signature);
  String s = find_s(serialized_signature);
  String v = String(_v, HEX);
  v.toLowerCase();
  if (r.charAt(0) == '0' && r.charAt(1) == '0') {
    r = r.substring(2);
  }
  tx->r = r;
  tx->s = s;
  tx->v = v;
  return rlpEncodeTx(tx);
}


String find_r(unsigned char * data){
  String r;
  for (int i = 0; i < 32; i++) {
    if (data[i] < 0x10) { r += '0'; }
    r += String(data[i], HEX);
  }
  return r;
}


String find_s(unsigned char * data) {
  String s;
  for (int i = 32; i < 64; i++) {
    if (data[i] < 0x10) { s += '0'; }
    s += String(data[i], HEX);
  }
  return s;
}


String generateKeccakHash(String txEncoded) {
  Keccak keccak;
  
  size_t bufLength = (txEncoded.length() - 2) / 2;
  uint8_t buf[bufLength];
  stringToUint(txEncoded, buf);
  
  std::string _hash = keccak(buf, bufLength);
  return _hash.c_str();
}


void stringToUint(String input, uint8_t* output) {
  int index = 0;

  if (input.charAt(0) == '0' && input.charAt(1) == 'x') {
    input = input.substring(2);
  }
  for (int i = 0; i < input.length(); i += 2) {
    unsigned char second = char2byte(input[i]);
    unsigned char first = char2byte(input[i+1]);
    output[index] = second*16 + first;
    index++;
  }
}


char char2byte(char input) {
  if (input >= 'a' && input <= 'f') {
    return input - 87;
  } else {
    return input - 48;
  }
}
