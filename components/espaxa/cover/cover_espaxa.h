#pragma once

#include "esphome/components/cover/cover.h"
#include "esphome/core/log.h"
#include "../espaxa.h"

namespace espaxa {

class EspAxaCover : public esphome::cover::Cover, public esphome::Component {
 public:
  void set_parent(EspAxa *p) { parent_ = p; }
  void setup() override {}
  void dump_config() override {}

 protected:
  esphome::cover::CoverTraits get_traits() override {
    esphome::cover::CoverTraits t;
    t.set_is_assumed_state(false);
    t.set_supports_stop(true);
    t.set_supports_position(true);   // <-- use this instead of set_supports_open/close
    // t.set_supports_tilt(false);   // optional
    return t;
  }

  void control(const esphome::cover::CoverCall &call) override {
    if (call.get_stop().has_value() && *call.get_stop())
      parent_->cmd_stop();

    if (call.get_position().has_value()) {
      float pos = *call.get_position();
      if (pos >= 0.5f) parent_->cmd_open();
      else             parent_->cmd_close();
    }
  }

  void loop() override {
    int code = parent_->read_status();
    if (code == AXA_OPENED) { this->position = 1.0f; this->publish_state(); }
    else if (code == AXA_CLOSED) { this->position = 0.0f; this->publish_state(); }
  }

 private:
  EspAxa *parent_{nullptr};
};

}  // namespace espaxa
