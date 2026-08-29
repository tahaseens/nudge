#pragma once

#include <optional>
#include <string>

namespace nudge
{

struct ControllerConfig
{
  std::optional<double> deadzone;
  std::optional<double> filter_alpha;
  std::string dpad_up_label;
  std::string dpad_right_label;
  std::string dpad_down_label;
  std::string dpad_left_label;
};

class ControllerConfigLoader
{
public:
  [[nodiscard]] static ControllerConfig load(const std::string& path);
};

}  // namespace nudge
