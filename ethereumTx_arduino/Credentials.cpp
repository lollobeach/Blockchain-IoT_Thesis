#include <WiFi.h>
#include <esp_wpa2.h>
#include "Credentials.h"


void connectWPA2() {
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

void connectWPA2Enterprise() {
  const char* ssid = "";
  const char* username = "";
  const char* password = "";
  
  WiFi.disconnect(true);
  WiFi.mode(WIFI_STA);
  esp_wifi_sta_wpa2_ent_set_identity((uint8_t *)username, strlen(username));
  esp_wifi_sta_wpa2_ent_set_username((uint8_t *)username, strlen(username));
  esp_wifi_sta_wpa2_ent_set_password((uint8_t *)password, strlen(password));
  esp_wpa2_config_t config = WPA2_CONFIG_INIT_DEFAULT();
  esp_wifi_sta_wpa2_ent_enable(&config);
  WiFi.begin(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to the WiFi network");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}