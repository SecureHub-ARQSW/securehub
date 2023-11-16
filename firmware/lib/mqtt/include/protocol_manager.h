// Copyright (c) 2023 SecureHub
// All rights reserved
#ifndef LIB_MQQT_INCLUDE_MQQT_H_
#define LIB_MQQT_INCLUDE_MQQT_H_

#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <string>
#include <WiFi.h>

namespace shub {

class ProtocolManager {
 public:
  ProtocolManager(std::string const& ssid, std::string const& password);
  
  virtual ~ProtocolManager() = default;

  bool ConnectToWifi();
  void VerifyWifiConnection();
  void PrintIpAddress();
  void ConnectToMqtt(std::string const& mqtt_broker, int mqtt_port,
    std::string const& mqtt_user, std::string const& device_token,
    std::string const& device_name);
  std::string SerializeJson(std::string const& variable_name, double value, std::string const& unit="");
  void PublishMessage(std::string const& topic, std::string const& payload);
  void ClientLoop() { mqtt_client_.loop(); };

  std::string GetSsid() const { return ssid_; };
  std::string GetPassword() const { return password_; };

 private:
  void TryConnection();

 private:
  std::string ssid_;
  std::string password_;

 private:
  WiFiClient wifi_client_;
  PubSubClient mqtt_client_;

};

}  // namespace shub

#endif  // LIB_MQQT_INCLUDE_MQQT_H_