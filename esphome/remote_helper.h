#include "esphome.h"

std::string build_remote_code(uint32_t identifier, uint8_t button_code, const std::vector<uint8_t>& rolling_codes, int& index) {
  index = (index + 1) % rolling_codes.size();
  
  uint32_t full_code = (identifier << 12) | (button_code << 8) | rolling_codes[index];
  
  std::string binary = "";
  for (int i = 31; i >= 0; i--) {
    binary += ((full_code >> i) & 1) ? "1" : "0";
  }
  
  ESP_LOGD("remote", "Sending code: %s (0x%08X)", binary.c_str(), full_code);
  
  return binary;
}