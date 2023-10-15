// Copyright (c) 2023 SecureHub
// All rights reserved

#ifndef LIB_UTILS_INCLUDE_HARDWARE_TYPES_H_
#define LIB_UTILS_INCLUDE_HARDWARE_TYPES_H_

#include <cstdint>

#include <esp32-hal-gpio.h>

namespace shub {

/**
 * Refers to the board pin number.
*/
using pin_t = uint32_t;

/**
 * Abstracts the Arduino macros for
 * the GPIO level.
*/
enum Level : uint8_t {
    kLow = LOW,
    kHigh = HIGH
};

/**
 * Abstracts the Arduino macros for
 * the pin internal pull resistor.
*/
enum PullConfig : uint8_t {
    kPullUp = INPUT_PULLUP,
    kPullDown = INPUT_PULLDOWN
};

enum Direction : uint8_t {
    kInput = INPUT,
    kOutput = OUTPUT
};

}  // namespace shub

#endif  // LIB_UTILS_INCLUDE_HARDWARE_TYPES_H_
