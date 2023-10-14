// Copyright (c) 2023 SecureHub
// All rights reserved

#ifndef LIB_INPUT_MANAGER_INCLUDE_INPUT_MANAGER_H_
#define LIB_INPUT_MANAGER_INCLUDE_INPUT_MANAGER_H_

#include <queue>
#include <string>

namespace shub {
    
using InputReady = bool;

class InputManager {
public:
  explicit InputManager(size_t max_input_size);
  virtual ~InputManager() = default;

  InputReady ProcessData();

  void PushData(char data);

  std::string const& GetInputData() const;

  bool IsQueueEmpty() const;

private:
  InputReady ProcessData(char data);

private:
  size_t max_input_size_;
  std::string input_data_;
  std::queue<char> input_queue_;
};

}  // namespace shub

#endif  // LIB_INPUT_MANAGER_INCLUDE_INPUT_MANAGER_H_
