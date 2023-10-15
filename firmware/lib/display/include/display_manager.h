// Copyright (c) 2023 SecureHub
// All rights reserved

#ifndef LIB_DISPLAY_MANAGER_INCLUDE_DISPLAY_MANAGER_H_
#define LIB_DISPLAY_MANAGER_INCLUDE_DISPLAY_MANAGER_H_

#include <LiquidCrystal_I2C.h>

namespace shub {

using Display = LiquidCrystal_I2C;

class DisplayManager {
public:
  DisplayManager(Display &&display, size_t max_number_asterisks = 6);

  virtual ~DisplayManager() = default;

  void TurnOn();

  void AddAsterisk();

  void RemoveAsterisk();

  void ClearAsterisks();

  void ShowMainScreen();

  void ShowSuccessMessage();

  void ShowFailureMessage();

  size_t GetNumberAsterisks() const;

  size_t GetMaxNumberAsterisks() const;

  bool IsOn() const;

private:
  void ShowInfoMessage(char const* message);

private:
  Display display_;
  size_t number_asterisks_ = 0;
  size_t max_number_asterisks_;
  bool is_on_ = false;
};

}  // namespace shub

#endif  // LIB_DISPLAY_MANAGER_INCLUDE_DISPLAY_MANAGER_H_
