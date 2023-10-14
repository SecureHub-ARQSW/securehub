// Copyright (c) 2023 SecureHub
// All rights reserved

#include "keypad.h"

shub::Keypad::Keypad(MatrixKeypad const&& keypad) :
      keypad_(keypad) {}

char shub::Keypad::CheckPressedButton(uint32_t col) const {
  keypad_.WriteAllRows(Level::kHigh);
  char pressed_key = CheckColumm(col);
  keypad_.WriteAllRows(Level::kLow);
  return pressed_key;
}

char shub::Keypad::CheckPressedButton() const {
    keypad_.WriteAllRows(Level::kHigh);
    char key = kKeyNotPressed;
    for(int col = 0; col < 4; col++) {
      char pressed_key = CheckColumm(col);
      if(pressed_key != kKeyNotPressed) {
        key = pressed_key;
        break;
      }
    }
    keypad_.WriteAllRows(Level::kLow);
    return key;
}

shub::pin_t shub::Keypad::GetColumm(uint8_t col) const {
  return keypad_.GetColumm(col);
}

char shub::Keypad::CheckColumm(uint8_t col) const {
  char key = kKeyNotPressed;
  for(int row = 0; row < 4; row++) {
    keypad_.WriteRow(row, Level::kLow);
    if(keypad_.ReadColumm(col) == Level::kLow) {
      key = keypad_.GetKey(row, col);
      break;
    }
    keypad_.WriteRow(row, Level::kHigh);
  }
  return key;
}
