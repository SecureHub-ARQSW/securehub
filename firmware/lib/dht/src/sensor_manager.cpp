
// Copyright (c) 2023 SecureHub
// All rights reserved

#include "sensor_manager.h"

shub::SensorManager::SensorManager(SensorTemperature&& sensor) : sensor_(sensor) {
}

void shub::SensorManager::ProcessTemperature(unsigned long& previous, unsigned long& current) {
    float temperature_temp = 0;
    if (sensor_.read2(&temperature_temp, nullptr, nullptr) == SimpleDHTErrSuccess) {
        total_temperature_ += temperature_temp;
        samples_++;
    }

    if (current - previous >= 10000) {
        if (samples_ > 0) {
            temperature_ = total_temperature_ / samples_;
        }
        else {
            Serial.println("No valid readings during the interval.");
        }
        samples_ = 0;
        total_temperature_ = 0;
        previous = current;
    }
}

float shub::SensorManager::GetTemperature() {
    return temperature_;
}