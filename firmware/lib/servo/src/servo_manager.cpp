// Copyright (c) 2023 SecureHub
// All rights reserved

#include "servo_manager.h"

shub::ServoManager::ServoManager(pin_t pin) : pin_(pin) {
    servo_.attach(pin_);
}

void shub::ServoManager::SetAngle(uint8_t angle) {
    servo_.write(angle);
}

uint8_t shub::ServoManager::GetAngle() const {
    return servo_.read();
}

void shub::ServoManager::Attach() {
    servo_.attach(pin_);
}

void shub::ServoManager::Detach() {
    servo_.detach();
}

bool shub::ServoManager::IsAttached() const {
    return servo_.attached();
}