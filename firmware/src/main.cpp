// Copyright (c) 2023 SecureHub
// All rights reserved

#include <queue>

#include <Arduino.h>

#include "input_processor.h"
#include "keypad.h"
#include "password_manager.h"
#include "protocol_manager.h"
#include "buzzer_manager.h"
#include "display_manager.h"
#include "sensor_manager.h"
#include "servo_manager.h"

shub::Keypad keypad(shub::MatrixKeypad({13, 12, 14, 27}, {26, 25, 33, 32}));
shub::InputProcessor input_processor(6);
shub::PasswordManager password_manager({"12345", "54321"});
shub::BuzzerManager buzzer_manager(shub::Buzzer(19));
shub::DisplayManager display_manager(shub::Display(0x3F, 16, 2));
shub::SensorManager sensor_manager(shub::TemperatureSensor(4));
// shub::ProtocolManager protocol_manager("Lost", "samuel1234");
// shub::ProtocolManager protocol_manager("MOB-JOAO VICTOR", "9846969400");
shub::ProtocolManager protocol_manager("VEX_1369_ANDERSON", "12345678");
shub::ServoManager servo_manager(15);

void KeypadHandleInput(uint8_t col);

unsigned long temperature_time = 0;
unsigned long lock_time = 0;
unsigned long previous_time = 0;

void setup() {
  Serial.begin(115200);
  display_manager.TurnOn();
  Serial.println("Starting...");

  protocol_manager.ConnectToWifi();
  protocol_manager.ConnectToMqtt("mqtt.tago.io", 1883, "Default", "0b85a2cd-8762-4c97-a960-35c34f7bb9c0", "ESP32-SHUB");
  Serial.printf("Payload: \n%s\n", protocol_manager.SerializeJson("temperature", 25.6, "ºC").c_str());
  protocol_manager.PublishMessage("info/lock", protocol_manager.SerializeJson("lock", 1));

  attachInterrupt(digitalPinToInterrupt(keypad.GetColumm(0)), []() {
    KeypadHandleInput(0);
  }, FALLING);

  attachInterrupt(digitalPinToInterrupt(keypad.GetColumm(1)), []() {
    KeypadHandleInput(1);
  }, FALLING);

  attachInterrupt(digitalPinToInterrupt(keypad.GetColumm(2)), []() {
    KeypadHandleInput(2);
  }, FALLING);

  attachInterrupt(digitalPinToInterrupt(keypad.GetColumm(3)), []() {
    KeypadHandleInput(3);
  }, FALLING);
}

void loop() {
  unsigned long current_time = millis();

  buzzer_manager.PlayLoadedSequence();

  if(input_processor.IsPending()) {

    if(display_manager.GetNumberAsterisks() == 0) {
      display_manager.ShowMainScreen();
    }

    if(input_processor.GetLastInput() == shub::FunctionKey::kClear) {
      display_manager.ClearAsterisks();
      display_manager.ShowMainScreen();
    }
    else if(input_processor.GetLastInput() == shub::FunctionKey::kRemove) {
      display_manager.RemoveAsterisk();
    }
    else if(input_processor.GetLastInput() != shub::FunctionKey::kDone) {
      display_manager.AddAsterisk();
    }

    shub::InputReady is_input_ready = input_processor.ProcessData();

    bool is_correct_password;
    if(is_input_ready && !input_processor.GetInputData().empty()) {
      std::string password_input = input_processor.ExtractData();
      bool is_correct_password = password_manager.TestPassword(password_input);
      if(is_correct_password) {
        buzzer_manager.PlaySuccessSequence();
        display_manager.ShowSuccessMessage();
        protocol_manager.PublishMessage("info/lock", protocol_manager.SerializeJson("lock", 0));
        servo_manager.SetAngle(180);
        lock_time = current_time;
      } else {
        buzzer_manager.PlayFailureSequence();
        display_manager.ShowFailureMessage();
        protocol_manager.PublishMessage("info/lock", protocol_manager.SerializeJson("lock", 2));
        servo_manager.SetAngle(0);
        lock_time = current_time;
      }
      display_manager.ClearAsterisks();
    }
  }

  sensor_manager.ProcessTemperature(previous_time, current_time);

  protocol_manager.VerifyWifiConnection();
  
  protocol_manager.ClientLoop();

  if(current_time - temperature_time >= shub::kPeriodSendTemperature){
    protocol_manager.PublishMessage("info/temperature", protocol_manager.SerializeJson("temperature", sensor_manager.GetTemperature(), "ºC"));

    temperature_time = current_time;
  }

  if(current_time - lock_time >= 4000) {
    lock_time = current_time;
    // Serial.println(servo_manager.GetAngle());
    if (servo_manager.GetAngle() == 179) {
      protocol_manager.PublishMessage("info/lock", protocol_manager.SerializeJson("lock", 1));
      servo_manager.SetAngle(0);
      display_manager.ShowMainScreen();
    } 
  }
}

void KeypadHandleInput(uint8_t col) {
  char pressed_key = keypad.CheckPressedButton(col);
  if(shub::Keypad::IsKeyValid(pressed_key)) {
    if(pressed_key != shub::FunctionKey::kDone) {
      buzzer_manager.LoadInputSequence();
    }
    input_processor.PushData(pressed_key);
  }
}
