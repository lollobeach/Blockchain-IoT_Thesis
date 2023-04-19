# Blockchain-IoT_Thesis

This is a project in which the **Blockchain** and **IoT** are used to safely track Cetara anchovies.
The work was carried out in collaboration with *BilancioCO2 Zero*, a Unicam spinoff, and *Silthenia S.r.l*, a startup from Montedinove (AP). 

It is complementary to that of Riccardo Petracci, a fellow magistral that has developed an IoT device that records the various GPS informations and uploads it to a Database.
What was missing was the development of an Arduino library to send tracking data (latitude, longitude, altitude, unixtime, device id and box fish id) to the Blockchain and of a *Smart Contract* that receive these to uploads them to this protocol.

## Technologies used

### Blockchain side:
- [Hyperledger Besu](https://besu.hyperledger.org/en/stable/);
- [Solidity](https://docs.soliditylang.org/en/v0.8.17/);
- [Remix](https://remix-project.org/);
- [Truffle](https://trufflesuite.com/docs/);
- [web3.js](https://web3js.org/#/).

### IoT side:
- [Arduino](https://www.arduino.cc/);
- [ESP32](https://en.wikipedia.org/wiki/ESP32);
- [Lilygo SIM7000G](http://www.lilygo.cn/prod_view.aspx?TypeId=50033&Id=1246&FId=t3:50033:3).

## Develop

The work focused on the creation, with Arduino, of a raw transaction to be sent via Json-RPC.
A module was written for the *RLP* encoding and an other for the signing mechanism with *ECDSA*.

The external library used for signature are:
- [keccak.k](https://github.com/stbrumme/hash-library/blob/master/keccak.h) for *Keccak256* hash;
- [secp256k1_recovery.h](https://github.com/diybitcoinhardware/secp256k1-embedded) for signature with *secp256k1* curve of ECDSA.

___

For privacy reason the sensitive data have been removed, so in order to use the Arduino library the code must be modified adding the missing information.

- In [Credentials.cpp](https://github.com/lollobeach/Blockchain-IoT_Thesis/blob/first_version/ethereumTx_arduino/Credentials.cpp) you must add:

the `ssid` and `password` in `connectWPA2()`;

```
  const char* ssid = "";
  const char* password = "";
```

or the `ssid`, `password` and `username` in `connectWPA2Enterprise()`.

```
  const char* ssid = "";
  const char* username = "";
  const char* password = "";
```

- In [RawTransaction.cpp](https://github.com/lollobeach/Blockchain-IoT_Thesis/blob/first_version/ethereumTx_arduino/RawTransaction.cpp) it is necessary to add:

the `public address` in `String createRawTransaction(String data, String privateKey)`. The public address must match the `privateKey`;

```
  String nonce = getNonce(/* public address */);
```

the `contract address` and `Chain Id` must also be added in this method;

```
  Tx tx = {nonce, "0x", gasLimit, /* contract address */, "0x", data, /* Chain ID */, "0x", "0x"};
```

in `String ecdsaSignature(String hash, String privateKey, Tx* tx)`, instead, it is sufficient to set the `Chain ID`.

```
  int _v = /* Chain ID */ * 2 + 35 + recid;
```

- In [RpcRequest.cpp](https://github.com/lollobeach/Blockchain-IoT_Thesis/blob/first_version/ethereumTx_arduino/RpcReqeust.cpp):

it's good to enter the `Ethereum node` and the `port` to which send Json-RPC request.

```
  const char server[] = /* Ethereum node */;
  const int port = /* port */;
```

- At the end you must modified the file [ethereumTx_arduino.ino](https://github.com/lollobeach/Blockchain-IoT_Thesis/blob/first_version/ethereumTx_arduino/ethereumTx_arduino.ino):

first you have to connect the board to WiFi with `connectWPA2()` or `connectWPA2Enterprise()` and then create the `dataField` with information needed.

```
  String dataField = createDataField(/* latitude, longitude, altitude, unixTime, device, fishCode, date */);
```

This variable, with the `private key` is used to create the raw transaction

```
  String rawTx = createRawTransaction(dataField, /* insert own private key */);
```

to be sent with `sendRawTransaction(rawTx)` that return the transaction hash if there isn't problems.

___

For testing with `web3.js` it is necessary to edit the [.env](https://github.com/lollobeach/Blockchain-IoT_Thesis/blob/first_version/besuDeploy/.env) file:

```
  HOST=#ethereum_node

  CONTRACT_ADDRESS=#contract_address

  ADMIN_KEY=#private_key_admin
  FIRST_DEVICE=#private_key_firstDevice
  SECOND_DEVICE=#private_key_secondDevice
```

`FIRST_DEVICE` and `SECOND_DEVICE` are the device added for the tracking with:

```
  const tx = contract.methods.addDevice(index, /* public address of the device to be added */)
```

The `ADMIN_KEY` must match the public address in the method `addDevice(bytes32 _idDevice, address _deviceAddress)` of the Solidity [Smart Contract](https://github.com/lollobeach/Blockchain-IoT_Thesis/blob/first_version/besuDeploy/contracts/Traceability.sol):

```
  require(msg.sender == /* Admin public address */, "Only admin can add addresses");
```
