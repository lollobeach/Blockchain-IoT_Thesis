# Blockchain-IoT_Thesis

This is a project in wich the **Blockchain** and **IoT** are used to safely track Cetara anchovies.
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
- [secp256k1_recovery.h](https://github.com/bitcoin-core/secp256k1/blob/master/include/secp256k1_recovery.h) for signature with *secp256k1* curve of ECDSA.

___

For privacy reason the sensitive data have been removed, so in order to use the Arduino library the code must be modified adding the missing information.

- In [Credentials.cpp](https://github.com/lollobeach/Blockchain-IoT_Thesis/blob/master/ethereumTx_arduino/Credentials.cpp) you must add:

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

## TO BE FINISHED
