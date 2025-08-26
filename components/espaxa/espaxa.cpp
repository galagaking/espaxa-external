#include "espaxa.h"
#include <cstring>

using namespace esphome;

namespace espaxa {

static const char *const TAG = "espaxa";

void EspAxa::setup() {
  ESP_LOGCONFIG(TAG, "Setting up AXA UART base component...");
  this->buf_len_ = 0;
}

void EspAxa::loop() {
  this->parse_available_();

  const uint32_t now = millis();
  if (this->last_query_ms_ == 0 || now - this->last_query_ms_ > QUERY_INTERVAL_MS) {
    this->last_query_ms_ = now;
    while (this->available()) this->read();
    this->send_line_("");
    this->send_line_("STATUS");
  }
}

void EspAxa::dump_config() {
  ESP_LOGCONFIG(TAG, "EspAxa (AXA Remote 2.0 over UART)");
}

void EspAxa::cmd_open() { this->send_line_("OPEN"); }
void EspAxa::cmd_close() { this->send_line_("CLOSE"); }
void EspAxa::cmd_stop()  { this->send_line_("STOP");  }

void EspAxa::send_line_(const char *s) {
  const char *p = s;
  while (*p) this->write(*p++);
  this->write('\r');
  this->write('\n');
  this->flush();
}

void EspAxa::poll_status_() { this->send_line_("STATUS"); }

void EspAxa::parse_available_() {
  while (this->available()) {
    uint8_t b = this->read();
    if (b == '\r') continue;
    if (b == '\n') {
      if (this->buf_len_ > 0) {
        this->buf_[this->buf_len_] = 0;
        this->handle_line_(reinterpret_cast<const char *>(this->buf_), this->buf_len_);
        this->buf_len_ = 0;
      }
      continue;
    }
    if (this->buf_len_ < BUFSZ - 1) this->buf_[this->buf_len_++] = b;
    else this->buf_len_ = 0;
  }
}

void EspAxa::handle_line_(const char *line, size_t len) {
  if (len < 3) return;
  int code = (line[0] - '0') * 100 + (line[1] - '0') * 10 + (line[2] - '0');
  this->last_status_ = code;
  ESP_LOGD(TAG, "AXA reply: %.*s -> %d", (int)len, line, code);
}

}  // namespace espaxa
