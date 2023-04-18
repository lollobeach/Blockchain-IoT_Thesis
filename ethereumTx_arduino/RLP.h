#ifndef RLP_h
#define RLP_h

#include "Tx.h"
#include <Arduino.h>

/**
 * Method that applies the RLP encoding
 * at the parameters list of the transaction.
 * 
 * Input:
 *  - Tx* tx, struct reference of the transaction
 *      to be encoded
 * 
 * Output:
 *  - String, hexadecimal string of the tx encoded
*/
String rlpEncodeTx(Tx* tx);

/**
 * Method that remove the '0x' annotation
 * from the string so that it can be encoded.
 * This method is called by rlpEncodeTx to
 * encode each parameter.
 * 
 * Input:
 *  - String input, parameter to be encoded
 * 
 * Output:
 * - String, parameter encoded
*/
String hexToRlp(String input);

/**
 * Method that applies the RLP encoding
 * at the single string. This method is called by
 * hexToRlp to encode the tx parameter.
 * 
 * Input:
 *  - String input, string to be encoded
 * 
 * Output:
 *  - String, string encoded
*/
String rlp_encode(String input);

/**
 * Method applying RLP rules for
 * bytes string with a single byte larger
 * than 0x80 or with more than one byte.
 * This method is called by rlp_encode.
 * 
 * Input:
 *  - String input, string to be encoded
 *  - int offset, according to rules is 128
 * 
 * Output:
 *  - String, string encoded
*/
String encodeLength(String input, int offset);

/**
 * Method used to calculate the length in bytes
 * of an hexadecimal string that represents a series
 * of bytes.
 * This method is used by encodeLength.
 * 
 * Input:
 *  - String s, input string of which you want to
 *      know the length in bytes
 * 
 * Output:
 *  - int, the length in bytes of the string
*/
int bytesLength(String s);

#endif
