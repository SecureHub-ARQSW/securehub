// Copyright (c) 2023 SecureHub
// All rights reserved

#include "protocol_manager.h"

shub::ProtocolManager::ProtocolManager(std::string const& ssid, std::string const& password) : ssid_(ssid), password_(password), 
    mqtt_client_(wifi_client_) {

}

void shub::ProtocolManager::PrintIpAddress() {
    Serial.printf("WiFi   : IP address: %s\n", WiFi.localIP().toString().c_str());
}

bool shub::ProtocolManager::ConnectToWifi() {
    Serial.printf("WiFi   : Connecting to %s\n", ssid_.c_str());
    WiFi.mode(WIFI_STA);  
    WiFi.begin(ssid_.c_str(), password_.c_str());
    TryConnection();
    Serial.println("");
    PrintIpAddress();
    WiFi.setAutoReconnect(true);
    WiFi.persistent(true);
    return true;
}

void shub::ProtocolManager::TryConnection() {
    int counter = 0;
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        counter++;
        if(counter > 20) {
            ESP.restart();
        }
    }
}

void shub::ProtocolManager::VerifyWifiConnection() {
    if(WiFi.status() != WL_CONNECTED || WiFi.localIP() == INADDR_NONE) {
        Serial.println("WiFi   : WiFi not connected, reconnecting");

        WiFi.disconnect();
        ConnectToWifi();
    }
}

void shub::ProtocolManager::ConnectToMqtt(std::string const& mqtt_broker, int mqtt_port,
    std::string const& mqtt_user, std::string const& device_token,
    std::string const& device_name) {

    if(!mqtt_client_.connected()) {
        Serial.println("MQTT   : Not connected to MQTT broker");

        mqtt_client_.setServer(mqtt_broker.c_str(), mqtt_port);
        mqtt_client_.setBufferSize(1024);

        Serial.println("MQTT   : Trying Connection to MQTT broker");

        if(mqtt_client_.connect(device_name.c_str(), mqtt_user.c_str(), device_token.c_str())) {
            Serial.printf("MQTT   : Connected to MQTT broker  %s:%d\n", mqtt_broker.c_str(), mqtt_port);
        } else {
            Serial.println("MQTT   : Failed to connect to MQTT broker");
            Serial.printf("MQTT   : Error code: %d", mqtt_client_.state());
            delay(5000);
            ConnectToWifi();
        }
    }
}

std::string shub::ProtocolManager::SerializeJson(std::string const& variable_name, double value, std::string const& unit) {
    StaticJsonDocument<200> doc;
    doc["variable"] = variable_name;
    doc["value"] = value;
    if(unit != "") {
        doc["unit"] = unit;
    }
    std::string output;
    serializeJson(doc, output);
    return output;
}

void shub::ProtocolManager::PublishMessage(std::string const& topic, std::string const& payload) {
    if(mqtt_client_.publish(topic.c_str(), payload.c_str())) {
        Serial.printf("MQTT   : Published message to topic %s\n", topic.c_str());
    } else {
        Serial.printf("MQTT   : Failed to publish message to topic %s\n", topic.c_str());
    }
}