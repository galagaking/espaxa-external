#pragma once
#include "esphome/components/sensor/sensor.h"
#include "../espaxa.h"

namespace espaxa {

class EspAxaStatusSensor : public esphome::sensor::Sensor, public esphome::Component {
 public:
  void set_parent(EspAxa *p) { parent_ = p; }
  void setup() override {}
  void loop() override {
    int s = parent_->read_status();
    // publish_state(s); // enable when needed
  }
 private:
  EspAxa *parent_{nullptr};
};

}  // namespace espaxa
