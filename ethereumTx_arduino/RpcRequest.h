#ifndef RpcRequest_h
#define RpcRequest_h

#include <Arduino.h>

/**
 * Method that send the POST request
 * to the Ethereum node for the
 * Json-RPC request.
 * 
 * Input:
 *  - String params, json params
 *      of the Json-RPC request
 * 
 * Output:
 *  - String, string of the response
*/
String sendRequest(String params);

/**
 * Method to send the raw transasaction
 * with sendRequest.
 * 
 * Input:
 *  - String tx, the raw transaction to be sent
 * 
 * Output:
 *  - String, the hash of the transaction or the
 *      error message
*/
String sendRawTransaction(String tx);

/**
 * Method to get the nonce of the sender,
 * always via Json-RPC request with sendRequest.
 * 
 * Input:
 *  - String address, address of the sender
 *      of which you want to know the nonce
 * 
 * Output:
 *  - String, hexadecimal string of the nonce
*/
String getNonce(String address);

/**
 * Method to get the gas limit, always via
 * Json-RPC request with sendRequest.
 * 
 * Output:
 *  - String, hexadecimal string of the gas limit
*/
String getGasLimit();

#endif
