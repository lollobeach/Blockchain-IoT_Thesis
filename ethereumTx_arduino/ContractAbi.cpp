#include "ContractAbi.h";
#include <keccak.h>

String createDataField(String data) {
  Keccak keccak;

  std::string hash = keccak("trackProduct(bytes)");
  String methodSignature = hash.c_str();
  methodSignature = methodSignature.substring(0, 8);

  String locationData = "0000000000000000000000000000000000000000000000000000000000000020";
  
  String bytesData = addOffset(data);

  String bytesLength = stringLengthToHex((bytesData.length()) / 2);

  return "0x" + methodSignature + locationData + bytesLength + bytesData;
}

String addOffset(String input) {
  String output = stringToHex(input);
  int outputLength = output.length();
  if (outputLength < 64) {
    int offset = 64 - outputLength;
    for (int i = 0; i < offset; i++) {
      output += '0';
    }
  }
  return output;
}

String stringToHex(String input) {
  String output;
  for (int i = 0; i < input.length(); i++) {
    output += String(input.charAt(i), HEX);
  }
  return output;
}

String stringLengthToHex(int length) {
  String lengthInHex = String(length, HEX);
  int outputLength = lengthInHex.length();
  if (outputLength < 64) {
    String offsetString;
    int offset = 64 - outputLength;
    for (int i = 0; i < offset; i++) {
      offsetString += '0';
    }
    lengthInHex = offsetString + lengthInHex;
  }
  return lengthInHex;
}