#pragma once

#include "esphome/core/component.h"
#include "esphome/core/log.h"
#include "esphome/components/uart/uart.h"

namespace espaxa {

// AXA status codes
static const int AXA_OPENED = 210;  // "210 Unlocked"
static const int AXA_CLOSED = 211;  // "211 Strong Locked"

class EspAxa : public esphome::Component, public esphome::uart::UARTDevice {
 public:
  void setup() override;
  void loop() override;
  void dump_config() override;

  void cmd_open();
  void cmd_close();
  void cmd_stop();

  int read_status() const { return this->last_status_; }
  bool is_open() const { return this->last_status_ == AXA_OPENED; }
  bool is_closed() const { return this->last_status_ == AXA_CLOSED; }

 private:
  uint32_t last_query_ms_{0};
  static constexpr uint32_t QUERY_INTERVAL_MS = 30000;  // 30s

  static constexpr size_t BUFSZ = 64;
  uint8_t buf_[BUFSZ];
  size_t buf_len_{0};

  int last_status_{0};

  void send_line_(const char *s);
  void poll_status_();
  void parse_available_();
  void handle_line_(const char *line, size_t len);
};

}  // namespace espaxa
