// Copyright (c) 2023 SecureHub
// All rights reserved

#include <queue>

#include <Arduino.h>
#include <EspMQTTClient.h>

#include "keypad.h"
#include "input_processor.h"
#include "password_manager.h"

shub::Keypad keypad(shub::MatrixKeypad({13, 12, 14, 27}, {26, 25, 33, 32}));
shub::InputProcessor input_processor(6);
shub::PasswordManager password_manager({"12345", "54321"});

void KeypadHandleInput(uint8_t col);

void setup() {
  Serial.begin(115200);

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
  if(input_processor.IsPending()) {
    shub::InputReady is_input_ready = input_processor.ProcessData();
    Serial.printf("CURRENT DATA: %s\n", input_processor.GetInputData().c_str());
    if(is_input_ready) {
      std::string password_input = input_processor.ExtractData();
      bool is_correct_password = password_manager.TestPassword(password_input);
      if(is_correct_password) {
        Serial.printf("CONFIRMED!!!\n");
      } else {
        Serial.printf("NEGATED!!!\n");
      }
    }
  }
}

void KeypadHandleInput(uint8_t col) {
  char pressed_key = keypad.CheckPressedButton(col);
  if(shub::Keypad::IsKeyValid(pressed_key)) {
    input_processor.PushData(pressed_key);
  }
}
