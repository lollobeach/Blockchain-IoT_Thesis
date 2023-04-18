#ifndef RawTransaction_h
#define RawTransaction_h

#include "Tx.h"
#include <Arduino.h>

/**
 * Method to create the raw transaction.
 * 
 * Input:
 *  - String data, Contract ABI encoded string
 *  - char* privateKey, char array of private key
 *      to use for ECDSA signature
 * 
 * Output:
 *  - String, hexadecimal string of raw transaction
*/
String createRawTransaction(String data, String privateKey);

/**
 * Method used by createRawTransaction to applied the ECDSA
 * signature.
 * 
 * Input:
 *  - String hash, hexadecimal string of keccak256 hash
 *  - String privateKey, hexadecimal string of private key
 *  - Tx* tx, Tx struct reference to override parameters v,r,s
 * 
 * Output:
 *  - String, transaction with RLP coding and signature
*/
String ecdsaSignature(String hash, String privateKey, Tx* tx);

/**
 * Method used by ecdsaSignature to find r value.
 * 
 * Input:
 *  - unsigned char * data, bytes array of serialized signature
 * 
 * Output:
 * - String, r value
*/
String find_r(unsigned char * data);

/**
 * Method used by ecdsaSignature to find s value.
 * 
 * Input:
 *  - unsigned char * data, bytes array of serialized signature
 * 
 * Output:
 * - String, s value
*/
String find_s(unsigned char * data);

/**
 * Method used by createRawTransaction to generate
 * the keccak hash of transaction encoded in RLP.
 * 
 * Input:
 *  - String txEncoded, hexadecimal string of transaction encoded
 * 
 * Output:
 *  - String, hexadecimal string of the keccak hash
*/
String generateKeccakHash(String txEncoded);

/**
 * Method used by generateKeccakHash and ecdsaSignature to convert an
 * input hexadecimal string in a bytes array.
 * 
 * Input:
 *  - String input, input in hexadecimal string format
 * 
 * Output:
 *  - uint8_t* output, output in bytes format
*/
void stringToUint(String input, uint8_t* output);

/**
 * Method used by stringToUint to convert
 * the single character in a byte.
 * 
 * Input:
 *  - char input, character to be converted
 * 
 * Output:
 * - char, the corresponding byte
*/
char char2byte(char input);


#endif
