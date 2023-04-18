#ifndef ContractAbi_h
#define ContractAbi_h

#include <Arduino.h>


/**
 * Method for Contract ABI encoding of GPS data.
 * 
 * Input:
 *  - String latitude, latitude to be encoded
 *  - String longitude, longitude to be encoded
 *  - String altitude, altitude to be encoded
 *  - String unixTime, unixTIme to be encoded
 *  - String device, device Id to be encoded
 *  - String fishCode, fish box Id to be encoded 
 *  - String date, date in format gg/mm/yyyy to be encoded
 * 
 * Output:
 *  - String, the data paramater to be added to the raw transaction
*/
String createDataField(String latitude, String longitude, String altitude, String unixTime, String device, String fishCode, String date);

/**
 * Method to convert an input string in an hexadecimal string of 32 bytes for ABI encode.
 * The length of the result is 64 characters, two characters for each byte.
 * 
 * Input:
 *  - String input, message to be converted
 * 
 * Output:
 *  - String, message converted
*/
String stringToHex64(String input);

#endif
