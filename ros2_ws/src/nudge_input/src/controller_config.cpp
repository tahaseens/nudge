#include "nudge_input/controller_config.hpp"

#include <stdexcept>

#include <yaml-cpp/yaml.h>

namespace nudge
{
namespace
{

std::optional<double> optional_double(const YAML::Node& node)
{
  if (!node || node.IsNull()) {
    return std::nullopt;
  }
  return node.as<double>();
}

std::string required_string(const YAML::Node& node, const char* path)
{
  if (!node || node.IsNull()) {
    throw std::runtime_error(std::string("missing required configuration key: ") + path);
  }
  return node.as<std::string>();
}

}  // namespace

ControllerConfig ControllerConfigLoader::load(const std::string& path)
{
  const YAML::Node root = YAML::LoadFile(path);
  if (!root["input"] || !root["explicit_semantic_mapping"]) {
    throw std::runtime_error("controller configuration is missing required sections");
  }

  ControllerConfig config;
  config.deadzone = optional_double(root["input"]["deadzone"]);
  config.filter_alpha = optional_double(root["input"]["filter_alpha"]);
  const YAML::Node mapping = root["explicit_semantic_mapping"];
  config.dpad_up_label = required_string(mapping["dpad_up"], "explicit_semantic_mapping.dpad_up");
  config.dpad_right_label =
      required_string(mapping["dpad_right"], "explicit_semantic_mapping.dpad_right");
  config.dpad_down_label =
      required_string(mapping["dpad_down"], "explicit_semantic_mapping.dpad_down");
  config.dpad_left_label =
      required_string(mapping["dpad_left"], "explicit_semantic_mapping.dpad_left");
  return config;
}

}  // namespace nudge
