#pragma once

#include "esphome/components/sensor/sensor.h"
#include "esphome/core/log.h"
#include "../espaxa.h"

namespace espaxa {

class EspAxaStatusSensor : public esphome::sensor::Sensor, public esphome::Component {
 public:
  void set_parent(EspAxa *p) { parent_ = p; }

  void setup() override {
    // nothing to init
  }

  void loop() override {
    if (parent_ == nullptr) return;
    const int s = parent_->read_status();
    if (s != last_published_) {
      // Publish raw status code (e.g., 210/211/200/502)
      //this->publish_state(static_cast<float>(s));
      last_published_ = s;
    }
  }

 private:
    EspAxa *parent_{nullptr};
    int last_published_{INT32_MIN};
};

}  // namespace espaxa
