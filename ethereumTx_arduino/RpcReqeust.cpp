#include "RpcRequest.h"
#include <WiFi.h>
#include <ArduinoHttpClient.h>
#include <ArduinoJson.h>

// insert the Ethereum node and the port
const char server[] = /* Ethereum node */;
const int port = /* port */;

WiFiClient wifi;
HttpClient http = HttpClient(wifi,server,port);


String sendRequest(String params) {
  
  http.beginRequest();
  http.post("/");
  http.sendHeader("Content-Type", "application/json");
  http.sendHeader("Content-Length", params.length());
  http.beginBody();
  http.print(params);
  http.endRequest();

  int statusCode = http.responseStatusCode();
  String response = http.responseBody();
  
  if (statusCode != 200) {
    Serial.print("Error with code: ");
    Serial.println(statusCode);
    http.stop();
    return response;
  } else {
    char _response[response.length()];
    response.toCharArray(_response, response.length()+1);

    StaticJsonDocument<1024> out;
    deserializeJson(out, _response);
    
    String result = out["result"];

    if (result == "null") {
      http.stop();
      return response;
    } else {
      http.stop();
      return result;
    }
  }
}


String sendRawTransaction(String tx) {

  StaticJsonDocument<1024> doc;
  doc["jsonrpc"] = "2.0";
  doc["method"] = "eth_sendRawTransaction";
  doc["params"][0] = tx;
  doc["id"] = 1;

  String jsonParams;
  serializeJson(doc, jsonParams);
  Serial.print("JsonParams: ");
  Serial.println(jsonParams);
  
  String txHash = sendRequest(jsonParams);

  return txHash;  
}


String getNonce(String address) {

  StaticJsonDocument<256> doc;
  doc["jsonrpc"] = "2.0";
  doc["method"] = "eth_getTransactionCount";
  doc["params"][0] = address;
  doc["params"][1] = "latest";
  doc["id"] = 1;

  String jsonParams;
  serializeJson(doc, jsonParams);
  Serial.print("JsonParams: ");
  Serial.println(jsonParams);

  String nonce = sendRequest(jsonParams);
  
  if (nonce.charAt(2) == '0') {
    nonce = "0x";
  }

  return nonce;
}


String getGasLimit() {

  StaticJsonDocument<256> doc;
  doc["jsonrpc"] = "2.0";
  doc["method"] = "eth_getBlockByNumber";
  doc["params"][0] = "latest";
  doc["params"][1] = false;
  doc["id"] = 1;

  String jsonParams;
  serializeJson(doc, jsonParams);
  Serial.print("JsonParams: ");
  Serial.println(jsonParams);

  String blockInfo = sendRequest(jsonParams);

  char _blockInfo[blockInfo.length()];
  blockInfo.toCharArray(_blockInfo, blockInfo.length()+1);

  StaticJsonDocument<1024> out;
  deserializeJson(out, _blockInfo);
  
  const char* _gasLimit = out["gasLimit"]; 

  return String(_gasLimit);
}
