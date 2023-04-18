#include "Tx.h"
#include "RawTransaction.h"
#include "Credentials.h"
#include "ContractAbi.h"
#include "RpcRequest.h"
#include "env.h"
#include <ArduinoJson.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  connectWPA2Mobile();

  String dataField = createDataField(/* json data */);

  String rawTx = createRawTransaction(dataField, PRIVATE_KEY);

  Serial.print("Data field: ");
  Serial.println(dataField);

  Serial.print("Raw tx: ");
  Serial.println(rawTx);

  String txHash = sendRawTransaction(rawTx);

  Serial.print("Tx hash: ");
  Serial.println(txHash);

}

void loop() {
  // put your main code here, to run repeatedly:
}
