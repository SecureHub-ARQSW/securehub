// Copyright (c) 2023 SecureHub
// All rights reserved

#include "input_processor.h"

#include "keypad.h"

shub::InputProcessor::InputProcessor(size_t max_input_size) :
      max_input_size_(max_input_size) {}

shub::InputReady shub::InputProcessor::ProcessData() {
  while(!input_queue_.empty()) {
    char data = input_queue_.front();
    input_queue_.pop();
    if(ProcessData(data)) {
      return true;
    }
  }
  return false;
}

void shub::InputProcessor::PushData(char data) {
  input_queue_.push(data);
}

std::string shub::InputProcessor::ExtractData() {
  std::string input_data = input_data_;
  input_data_.clear();
  return input_data;
}

std::string const& shub::InputProcessor::GetInputData() const {
  return input_data_;
}

shub::InputReady shub::InputProcessor::ProcessData(char data) {
  switch(data) {
    default:
      if(input_data_.size() <= max_input_size_) {
        input_data_.push_back(data);
      }
      break;

    case FunctionKey::kRemove:
      if(!input_data_.empty()) {
        input_data_.pop_back();
      }
      break;

    case FunctionKey::kClear:
      input_data_.clear();
      break;

    case FunctionKey::kDone:
      input_queue_ = {};
      return true;
  }

  return false;
}

bool shub::InputProcessor::IsPending() const {
  return !input_queue_.empty();
}