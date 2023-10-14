// Copyright (c) 2023 SecureHub
// All rights reserved

#include "input_manager.h"

enum InputAction : char {
  kDone = 'A',
  kRemove = 'B',
  kClear = 'C'
};

shub::InputManager::InputManager(size_t max_input_size) :
      max_input_size_(max_input_size) {}

shub::InputReady shub::InputManager::ProcessData() {
  while(!input_queue_.empty()) {
    char data = input_queue_.front();
    input_queue_.pop();
    if(ProcessData(data)) {
      return true;
    }
  }
  return false;
}

void shub::InputManager::PushData(char data) {
  input_queue_.push(data);
}

std::string const& shub::InputManager::GetInputData() const {
  return input_data_;
}

shub::InputReady shub::InputManager::ProcessData(char data) {
  switch(data) {
    default:
      if(input_data_.size() <= max_input_size_) {
        input_data_.push_back(data);
      }
      break;

    case InputAction::kRemove:
      if(!input_data_.empty()) {
        input_data_.pop_back();
      }
      break;

    case InputAction::kClear:
      input_data_.clear();
      break;

    case InputAction::kDone:
      input_queue_ = {};
      return true;
  }

  return false;
}

bool shub::InputManager::IsQueueEmpty() const {
  return input_queue_.empty();
}