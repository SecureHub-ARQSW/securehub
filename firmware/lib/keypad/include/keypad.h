// Copyright (c) 2023 SecureHub
// All rights reserved

#ifndef LIB_KEYPAD_INCLUDE_KEYPAD_H_
#define LIB_KEYPAD_INCLUDE_KEYPAD_H_

#include <matrix_keypad.h>

namespace shub {

class Keypad {
public:
  explicit Keypad(MatrixKeypad const&& keypad);

  virtual ~Keypad() = default;
  
  char CheckPressedButton(uint32_t col) const;

  char CheckPressedButton() const;

  pin_t GetColumm(uint8_t col) const;

public:
  static constexpr char kKeyNotPressed = -1;

private:
  char CheckColumm(uint8_t col) const;

private:
  MatrixKeypad keypad_;
};

}  // namespace shub

#endif  // LIB_KEYPAD_INCLUDE_KEYPAD_H_
