// Copyright (c) 2023 SecureHub
// All rights reserved
#ifndef LIB_MQQT_INCLUDE_MQQT_H_
#define LIB_MQQT_INCLUDE_MQQT_H_

#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <string>
#include <WiFi.h>
#include <WiFiClientSecure.h>

namespace shub {

class ProtocolManager {
 public:
  ProtocolManager(std::string const& ssid, std::string const& password,
    std::string const& mqtt_broker, uint8_t mqtt_port,
    std::string const& mqtt_user, std::string const& device_token,
    std::string const& device_name);
  
  virtual ~ProtocolManager() = default;

  bool ConnectToWifi();
  void VerifyWifiConnection();
  void PrintIpAddress();
  void ConnectToMqtt();
  std::string SerializeJson(std::string const& variable_name, double value);
  std::string SerializeJson(std::string const& variable_name, double value, std::string const& unit);
  void PublishMessage(std::string const& topic, int value);

 public:
  std::string ssid_;
  std::string password_;
  std::string mqtt_broker_;
  uint8_t mqtt_port_;
  std::string mqtt_user_;
  std::string device_token_;
  std::string device_name_;

 private:
  WiFiClientSecure wifi_client_;
  PubSubClient mqtt_client_;

};

}  // namespace shub

#endif  // LIB_MQQT_INCLUDE_MQQT_H_