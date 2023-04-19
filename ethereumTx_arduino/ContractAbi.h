#ifndef ContractAbi_h
#define ContractAbi_h

#include <Arduino.h>


/**
 * Method for Contract ABI encoding of GPS data.
 * 
 * Input:
 *  - String jsonData, a JSON string that contains all informations
 * 
 * Output:
 *  - String, the data paramater to be added to the raw transaction
*/
String createDataField(String jsonData);

/**
 * Method to add offset according to Contract ABI Specification
 * 
 * Input:
 *  - String input, it corresponds to the input of 'createDataField()' method
 *
 * Output:
 * - String, the data with offset
*/
String addOffset(String input):

/**
 * Method to convert an input string in an hexadecimal string for ABI encode.
 * 
 * Input:
 *  - String input, message to be converted
 * 
 * Output:
 *  - String, message converted
*/
String stringToHex(String input);

/**
* Method that returns the length of string in hex according to the
* Contract Abi Specification
*
* Input:
*  - int length, length in bytes of the input of 'createDataFieldMethod()'
*       converted in bytes
*
* Output:
* - String, bytes length of input with hexadecimal rapresentation
*/
String stringLengthToHex(int length);

#endif
