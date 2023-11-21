// Copyright (c) 2023 SecureHub
// All rights reserved

#ifndef LIB_SERVO_INCLUDE_SERVO_MANAGER_H_
#define LIB_SERVO_INCLUDE_SERVO_MANAGER_H_

#include <Servo.h>

#include "hardware_types.h"

namespace shub {

class ServoManager {
    public:
        ServoManager(pin_t pin);
        void SetAngle(uint8_t angle);
        uint8_t GetAngle() const;
        void Attach();
        void Detach();
        bool IsAttached() const;

    private:
        Servo servo_;
        pin_t pin_;
};

}  // namespace shub

#endif  // LIB_SERVO_INCLUDE_SERVO_MANAGER_H_