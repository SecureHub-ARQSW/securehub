// Copyright (c) 2023 SecureHub
// All rights reserved

#ifndef LIB_BUZZER_MANAGER_INCLUDE_BUZZER_MANAGER_H_
#define LIB_BUZZER_MANAGER_INCLUDE_BUZZER_MANAGER_H_

#include "buzzer.h"

namespace shub {

class BuzzerManager {
public:
  BuzzerManager(Buzzer &&buzzer);

  virtual ~BuzzerManager() = default;

  void PlaySuccessSequence() const;

  void PlayFailureSequence() const;

  void LoadInputSequence();

  void PlayLoadedSequence();

private:
  Buzzer buzzer_;
};

}  // namespace shub

#endif  // LIB_BUZZER_MANAGER_INCLUDE_BUZZER_MANAGER_H_
