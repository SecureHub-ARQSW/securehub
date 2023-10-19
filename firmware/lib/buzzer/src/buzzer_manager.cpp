// Copyright (c) 2023 SecureHub
// All rights reserved

#include "buzzer_manager.h"

shub::BuzzerManager::BuzzerManager(Buzzer &&buzzer) : 
      buzzer_(buzzer) {}

void shub::BuzzerManager::PlaySuccessSequence() const {
  buzzer_.Play(1568, 200);
  buzzer_.Play(0, 50);
  buzzer_.Play(1568, 200);
}

void shub::BuzzerManager::PlayFailureSequence() const {
  buzzer_.Play(131, 200);
  buzzer_.Play(0, 50);
  buzzer_.Play(131, 200);
}

void shub::BuzzerManager::LoadInputSequence() {
  buzzer_.LoadConfig(shub::BuzzerConfig(3520, 100));
}

void shub::BuzzerManager::PlayLoadedSequence() {
  if(!buzzer_.HasConfigPlayed()) {
    buzzer_.PlayConfig();
  }
}
