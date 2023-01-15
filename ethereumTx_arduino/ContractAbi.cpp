#include "ContractAbi.h";
#include <keccak.h>

String createDataField(String latitude, String longitude, String altitude, String unixTime, String device, String fishCode, String date) {
  Keccak keccak;
  
  std::string hash = keccak("trackProduct(bytes32,bytes32,bytes32,bytes32,bytes32,bytes32,bytes32)");
  String methodSignature = hash.c_str();
  methodSignature = methodSignature.substring(0,8);
  
  String _latitude = stringToHex64(latitude);
  String _longitude = stringToHex64(longitude);
  String _altitude = stringToHex64(altitude);
  String _unixTime = stringToHex64(unixTime);
  String _device = stringToHex64(device);
  String _fishCode = stringToHex64(fishCode);
  String _date = stringToHex64(date);
  
  return "0x" + methodSignature + _latitude + _longitude + _altitude + _unixTime + _device + _fishCode + _date;
}

String stringToHex64(String input) {
  String output;
  for (int i = 0; i < input.length(); i++) {
    output += String(input.charAt(i), HEX);
  }
  int offset = 64 - output.length();
  for (int i = 0; i < offset; i++) {
    output += '0';
  }
  return output;
}
