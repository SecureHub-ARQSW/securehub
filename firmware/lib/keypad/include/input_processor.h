// Copyright (c) 2023 SecureHub
// All rights reserved

#ifndef LIB_INPUT_PROCESSOR_INCLUDE_INPUT_PROCESSOR_H_
#define LIB_INPUT_PROCESSOR_INCLUDE_INPUT_PROCESSOR_H_

#include <queue>
#include <string>

namespace shub {
    
using InputReady = bool;

class InputProcessor {
public:
  explicit InputProcessor(size_t max_input_size);
  virtual ~InputProcessor() = default;

  InputReady ProcessData();

  void PushData(char data);

  std::string ExtractData();

  std::string const& GetInputData() const;

  char GetLastInput() const;

  bool IsPending() const;

private:
  InputReady ProcessData(char data);

private:
  size_t max_input_size_;
  std::string input_data_;
  std::queue<char> input_queue_;
};

}  // namespace shub

#endif  // LIB_INPUT_PROCESSOR_INCLUDE_INPUT_PROCESSOR_H_
