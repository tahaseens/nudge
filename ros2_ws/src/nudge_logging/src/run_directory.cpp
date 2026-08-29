#include "nudge_logging/run_directory.hpp"

#include <cctype>
#include <fstream>
#include <stdexcept>

namespace nudge
{
namespace
{

std::string safe_component(const std::string& value)
{
  if (value.empty()) {
    throw std::invalid_argument("run directory components must not be empty");
  }
  std::string safe;
  safe.reserve(value.size());
  for (const unsigned char character : value) {
    safe.push_back(std::isalnum(character) || character == '-' || character == '_' ?
                       static_cast<char>(character) :
                       '_');
  }
  return safe;
}

void write_file(const std::filesystem::path& path, const std::string& contents)
{
  std::ofstream stream(path, std::ios::out | std::ios::trunc);
  if (!stream) {
    throw std::runtime_error("unable to create logging scaffold file: " + path.string());
  }
  stream << contents;
}

}  // namespace

std::filesystem::path RunDirectory::create(const std::filesystem::path& runs_root,
                                           const std::string& timestamp,
                                           const std::string& scenario_id)
{
  const auto run_path = runs_root / (safe_component(timestamp) + "_" + safe_component(scenario_id));
  if (std::filesystem::exists(run_path)) {
    throw std::runtime_error("run directory already exists: " + run_path.string());
  }
  std::filesystem::create_directories(run_path / "rosbag2");

  write_file(run_path / "manifest.json",
             "{\n"
             "  \"run_id\": null,\n"
             "  \"timestamp\": \"" + safe_component(timestamp) + "\",\n"
             "  \"git_commit\": null,\n"
             "  \"scenario_id\": \"" + safe_component(scenario_id) + "\",\n"
             "  \"control_condition\": null,\n"
             "  \"operator_context\": null,\n"
             "  \"robot_assumed_goal\": null,\n"
             "  \"ground_truth_goal\": null,\n"
             "  \"intended_correction_type\": null,\n"
             "  \"objective_weights\": null,\n"
             "  \"confidence_thresholds\": null,\n"
             "  \"controller_config\": null,\n"
             "  \"map_id\": null\n"
             "}\n");
  write_file(run_path / "telemetry.csv",
             "timestamp,pose_x,pose_y,pose_yaw,velocity_linear,velocity_angular,"
             "human_linear,human_angular,autonomy_linear,autonomy_angular,executed_linear,"
             "executed_angular,autonomy_confidence,correction_confidence,"
             "environmental_confidence,authority_state,robot_assumed_goal,active_plan_id,"
             "human_input_active\n");
  write_file(run_path / "events.jsonl", "");
  return run_path;
}

}  // namespace nudge
