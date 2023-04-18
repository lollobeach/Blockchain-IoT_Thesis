#include <WiFi.h>
#include <esp_wpa2.h>
#include "Credentials.h"

void connectWPA2Mobile() {
    const char* ssid = "";
    const char* password = "";

    WiFi.begin(ssid,password);

    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println("Connecting to WiFi...");
    }

    Serial.println("Connected to the WiFi network");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
}

void connectWPA2Home() {
    const char* ssid = "";
    const char* password = "";

    WiFi.begin(ssid,password);

    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println("Connecting to WiFi...");
    }

    Serial.println("Connected to the WiFi network");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
}