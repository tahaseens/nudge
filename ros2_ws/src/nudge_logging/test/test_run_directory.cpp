#include <gtest/gtest.h>

#include <chrono>
#include <filesystem>
#include <fstream>
#include <sstream>

#include "nudge_logging/run_directory.hpp"

namespace
{

std::string read_all(const std::filesystem::path& path)
{
  std::ifstream stream(path);
  std::ostringstream contents;
  contents << stream.rdbuf();
  return contents.str();
}

}  // namespace

TEST(RunDirectory, CreatesRequiredLoggingContract) {
  const auto nonce = std::chrono::steady_clock::now().time_since_epoch().count();
  const auto root = std::filesystem::temp_directory_path() /
                    ("nudge_logging_test_" + std::to_string(nonce));
  const auto run = nudge::RunDirectory::create(root, "20260829T120000Z", "usar_route_02");

  EXPECT_EQ(run.filename(), "20260829T120000Z_usar_route_02");
  EXPECT_TRUE(std::filesystem::is_regular_file(run / "manifest.json"));
  EXPECT_TRUE(std::filesystem::is_regular_file(run / "telemetry.csv"));
  EXPECT_TRUE(std::filesystem::is_regular_file(run / "events.jsonl"));
  EXPECT_TRUE(std::filesystem::is_directory(run / "rosbag2"));

  const std::string manifest = read_all(run / "manifest.json");
  EXPECT_NE(manifest.find("\"control_condition\""), std::string::npos);
  EXPECT_NE(manifest.find("\"operator_context\""), std::string::npos);
  EXPECT_NE(manifest.find("\"confidence_thresholds\""), std::string::npos);

  std::filesystem::remove_all(root);
}
