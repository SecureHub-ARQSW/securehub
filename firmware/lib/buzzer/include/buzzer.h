// Copyright (c) 2023 SecureHub
// All rights reserved

#ifndef LIB_BUZZER_INCLUDE_BUZZER_H_
#define LIB_BUZZER_INCLUDE_BUZZER_H_

#include "hardware_types.h"

namespace shub {

struct BuzzerConfig {
  BuzzerConfig(uint32_t frequency = 0, uint32_t duration = 0);
  uint32_t frequency;
  uint32_t duration;
};

class Buzzer {
public:
  Buzzer(pin_t buzzer);

  virtual ~Buzzer() = default;

  void Play(uint32_t frequency, uint32_t duration) const;

  void Play(BuzzerConfig const& config) const;

  void PlayConfig();

  void LoadConfig(BuzzerConfig &&config);

  bool HasConfigPlayed() const;

private:
  const pin_t buzzer_;
  BuzzerConfig config_;
  bool has_config_played_;
};

}  // namespace shub

#endif  // LIB_BUZZER_INCLUDE_BUZZER_H_
