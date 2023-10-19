// Copyright (c) 2023 SecureHub
// All rights reserved

#include "display_manager.h"

shub::DisplayManager::DisplayManager(Display &&display, size_t max_number_asterisks) :
      max_number_asterisks_(max_number_asterisks),
      display_(display) {}
  
void shub::DisplayManager::TurnOn() {
  if(!is_on_) {
    display_.init();
    display_.backlight();
    ShowMainScreen();
    is_on_ = true;
  }
}

void shub::DisplayManager::AddAsterisk() {
  if(number_asterisks_ < max_number_asterisks_) {
    display_.setCursor(10 + number_asterisks_, 0);
    display_.print('*');
    number_asterisks_++;
  }
}

void shub::DisplayManager::RemoveAsterisk() {
  if(number_asterisks_ > 0) {
    number_asterisks_--;
    display_.setCursor(10 + number_asterisks_, 0);
    display_.print(' ');
  }
}

void shub::DisplayManager::ClearAsterisks() {
  number_asterisks_ = 0;
}

void shub::DisplayManager::ShowMainScreen() {
  display_.clear();
  display_.setCursor(0, 0);
  display_.print("Password: ");
}

void shub::DisplayManager::ShowSuccessMessage() {
  ShowInfoMessage("Correct Password");
}

void shub::DisplayManager::ShowFailureMessage() {
  ShowInfoMessage("Invalid Password");
}

size_t shub::DisplayManager::GetNumberAsterisks() const {
  return number_asterisks_;
}

size_t shub::DisplayManager::GetMaxNumberAsterisks() const {
  return max_number_asterisks_;
}

bool shub::DisplayManager::IsOn() const {
  return is_on_;
}

void shub::DisplayManager::ShowInfoMessage(char const* message) {
  display_.setCursor(0, 1);
  display_.print(message);
}
