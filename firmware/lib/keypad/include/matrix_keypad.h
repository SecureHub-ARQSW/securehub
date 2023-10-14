// Copyright (c) 2023 SecureHub
// All rights reserved

#ifndef LIB_KEYPAD_INCLUDE_MATRIX_KEYPAD_H_
#define LIB_KEYPAD_INCLUDE_MATRIX_KEYPAD_H_

#include <array>

#include <hardware_types.h>

namespace shub {

class MatrixKeypad {
public:
  MatrixKeypad(std::array<pin_t, 4> const&& rows, 
    std::array<pin_t, 4> const&& cols, 
    PullConfig pull_config = PullConfig::kPullUp);

  virtual ~MatrixKeypad() = default;

  void WriteRow(uint8_t row, Level level) const;

  void WriteAllRows(Level level) const;

  Level ReadColumm(uint8_t col) const;

  pin_t GetColumm(uint8_t col) const;

public:
  static char GetKey(uint8_t row, uint8_t col);

private:
  void SetupRows(Level level) const;
  void SetupColumms(PullConfig pull_config) const;

private:
  const std::array<pin_t, 4> rows_;
  const std::array<pin_t, 4> cols_;
};

}  // namespace shub

#endif  // LIB_KEYPAD_INCLUDE_MATRIX_KEYPAD_H_
