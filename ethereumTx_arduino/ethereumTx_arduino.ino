#include "Tx.h"
#include "RawTransaction.h"
#include "Credentials.h"
#include "ContractAbi.h"
#include "RpcRequest.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  // first of all you need to connect to the WiFi network
  connectWPA2();
  
  // you encode the data according to Contract ABI specification
  String dataField = createDataField(/* latitude, longitude, altitude, unixTime, device, fishCode, date */);

  // you create the raw transaction with data parameter and own private key
  String rawTx = createRawTransaction(dataField, /* insert own private key */);
  
  Serial.print("Data field: ");
  Serial.println(dataField);

  Serial.print("Raw tx: ");
  Serial.println(rawTx);

  // at the end you send the transaction
  String txHash = sendRawTransaction(rawTx);
  Serial.print("Tx hash: ");
  Serial.println(txHash);
  
}

void loop() {
  // put your main code here, to run repeatedly:
}
