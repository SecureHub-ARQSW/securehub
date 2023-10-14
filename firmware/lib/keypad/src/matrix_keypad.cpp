// Copyright (c) 2023 SecureHub
// All rights reserved

#include <matrix_keypad.h>

#include <Arduino.h>

constexpr std::array<std::array<char, 4>, 4> kMatrixKeypadKeys = 
  {{
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'},
  }};

shub::MatrixKeypad::MatrixKeypad(std::array<pin_t, 4> const &&rows,
    std::array<pin_t, 4> const &&cols,
    PullConfig pull_config) : 
      rows_(rows), cols_(cols) {
  if(pull_config == PullConfig::kPullUp) {
    SetupRows(Level::kLow);
  } else {
    SetupRows(Level::kHigh);
  }
  SetupColumms(pull_config);
}

void shub::MatrixKeypad::WriteRow(uint8_t row, Level level) const {
  digitalWrite(rows_.at(row), static_cast<uint8_t>(level));
}

void shub::MatrixKeypad::WriteAllRows(Level level) const {
  for(pin_t row : rows_) {
    digitalWrite(row, static_cast<uint8_t>(level));
  }
}

shub::Level shub::MatrixKeypad::ReadColumm(uint8_t col) const {
  return static_cast<Level>(digitalRead(cols_.at(col)));
}

shub::pin_t shub::MatrixKeypad::GetColumm(uint8_t col) const {
  return cols_.at(col);
}

char shub::MatrixKeypad::GetKey(uint8_t row, uint8_t col) {
  return kMatrixKeypadKeys.at(row).at(col);
}

void shub::MatrixKeypad::SetupRows(Level level) const {
  for(pin_t row : rows_) {
    pinMode(row, Direction::kOutput);
    digitalWrite(row, static_cast<uint8_t>(level));
  }
}

void shub::MatrixKeypad::SetupColumms(PullConfig pull_config) const {
  for(pin_t col : cols_) {
    pinMode(col, static_cast<uint8_t>(pull_config));
  }
}
