#include <gtest/gtest.h>

#include "nudge_input/controller_config.hpp"

TEST(ControllerConfig, LoadsNullResearchValuesWithoutInventingDefaults) {
  const auto config = nudge::ControllerConfigLoader::load(NUDGE_CONTROLLER_CONFIG);
  EXPECT_FALSE(config.deadzone.has_value());
  EXPECT_FALSE(config.filter_alpha.has_value());
}

TEST(ControllerConfig, LoadsExplicitSemanticMapping) {
  const auto config = nudge::ControllerConfigLoader::load(NUDGE_CONTROLLER_CONFIG);
  EXPECT_EQ(config.dpad_up_label, "MOTION");
  EXPECT_EQ(config.dpad_right_label, "PLAN");
  EXPECT_EQ(config.dpad_down_label, "GOAL");
  EXPECT_EQ(config.dpad_left_label, "AUTHORITY");
}
