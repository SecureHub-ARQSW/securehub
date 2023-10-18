// Copyright (c) 2023 SecureHub
// All rights reserved

#include "protocol_manager.h"

shub::ProtocolManager::ProtocolManager(std::string const& ssid, std::string const& password,
    std::string const& mqtt_broker, uint8_t mqtt_port,
    std::string const& mqtt_user, std::string const& device_token,
    std::string const& device_name) : ssid_(ssid), password_(password),
    mqtt_broker_(mqtt_broker), mqtt_port_(mqtt_port), mqtt_user_(mqtt_user),
    device_token_(device_token), device_name_(device_name), 
    wifi_client_(), mqtt_client_(wifi_client_) {

}

void shub::ProtocolManager::PrintIpAddress() {
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

bool shub::ProtocolManager::ConnectToWifi() {
    Serial.printf("Connecting to %s\n", ssid_.c_str());
    WiFi.mode(WIFI_STA);  
    WiFi.begin(ssid_.c_str(), password_.c_str());
    int counter = 0;
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        counter++;
        if(counter > 20) {
            ESP.restart();
        }
    }
    PrintIpAddress();
    return true;
}

void shub::ProtocolManager::VerifyWifiConnection() {
    if(WiFi.status() != WL_CONNECTED || WiFi.localIP() == INADDR_NONE) {
        Serial.println("Error: WiFi not connected, reconnecting");

        WiFi.disconnect();
        ConnectToWifi();
    }
}