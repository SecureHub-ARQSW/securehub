// Copyright (c) 2023 SecureHub
// All rights reserved 

#ifndef LIB_SENSOR_MANAGER_H
#define LIB_SENSOR_MANAGER_H

#include <SimpleDHT.h>

namespace shub {

    constexpr int kPeriodSendTemperature = 1000 * 60; // 1 minute 

    using TemperatureSensor = SimpleDHT22;

    class SensorManager {

    public:
        SensorManager(TemperatureSensor&& sensor);
        virtual ~SensorManager() = default;

        float GetTemperature();

        void ProcessTemperature(unsigned long& previous, unsigned long& current);

    private:
        TemperatureSensor sensor_;
        float temperature_ = 0;
        double total_temperature_ = 0;
        int samples_ = 0;
    };

} // namespace shub


#endif // LIB_SENSOR_MANAGER_H
