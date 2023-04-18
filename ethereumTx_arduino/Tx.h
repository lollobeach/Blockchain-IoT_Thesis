#ifndef Tx_h
#define Tx_h

#include <Arduino.h>

struct Tx {
  String nonce;
  String gasPrice;
  String gasLimit;
  String to;
  String value;
  String data;
  String v;
  String r;
  String s;
};

#endif
