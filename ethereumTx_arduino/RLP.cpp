#include "RLP.h"
#include "Tx.h"


String rlpEncodeTx(Tx* tx) {
  String serialized;
    serialized = hexToRlp(tx->nonce) +
                hexToRlp(tx->gasPrice) +
                hexToRlp(tx->gasLimit) +
                hexToRlp(tx->to) +
                hexToRlp(tx->value) +
                hexToRlp(tx->data) +
                hexToRlp(tx->v) +
                hexToRlp(tx->r) +
                hexToRlp(tx->s);                      
  int serializedLength = bytesLength(serialized);
  if (serializedLength <= 55) {
    char temp = 192 + serializedLength;
    return String(temp, HEX) + serialized;
  } else {
    String offset = String(serializedLength, HEX);
    if (offset.length() % 2 != 0) {
      offset = '0' + offset;
    }
    int initialByte = 247 + offset.length() / 2;
    String initialByteHex = String(initialByte, HEX);
    return "0x" + initialByteHex + offset + serialized;
  }
}


String hexToRlp(String s) {
  String str = s;
  if (s.charAt(0) == '0' && s.charAt(1) == 'x') {
    str = s.substring(2);
  }
  str.toLowerCase();
  return rlp_encode(str);
}


String rlp_encode(String input) {
  int length = input.length();
  if (length == 1) {
    return '0' + input;
  } else if (length == 2 && input.charAt(0) < '8') {
    return input;
  } else {
    return encodeLength(input, 128) + input;
  }
}


String encodeLength(String input, int offset) {
  int length = bytesLength(input);
  if (length < 56) {
    char myChar = length + offset;
    String result = String(myChar, HEX);
    if ((input.length() % 2) != 0) {
      return result + '0';
    } else {
      return result;
    }
  } else if (length < pow(256,8)) {
    String hexLength = String(length, HEX); 
    int bytesLength = hexLength.length() / 2;
    char temp = bytesLength + offset + 55;
    String toString = String(temp, HEX);
    String stringLen = String(length, HEX);
    String output = toString + stringLen;
    if ((input.length() % 2) != 0) {
      return output + '0';
    }
    return output;
  }
}


int bytesLength(String s) {
  String str = s;
  if (s.charAt(0) == '0' && s.charAt(1) == 'x') {
    str = s.substring(2);
  }
  int length = str.length();
  if ((length % 2) == 0) {
    return length / 2;
  } else {
    return (length + 1) / 2;
  }
}
