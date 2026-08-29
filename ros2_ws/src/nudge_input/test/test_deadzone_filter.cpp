#include <gtest/gtest.h>

#include <stdexcept>

#include "nudge_input/deadzone_filter.hpp"

TEST(DeadzoneFilter, ZerosValuesAtAndInsideBoundary) {
  const nudge::DeadzoneFilter filter(0.1);
  EXPECT_DOUBLE_EQ(filter.apply_axis(0.0), 0.0);
  EXPECT_DOUBLE_EQ(filter.apply_axis(0.1), 0.0);
  EXPECT_DOUBLE_EQ(filter.apply_axis(-0.1), 0.0);
}

TEST(DeadzoneFilter, PreservesOutsideValuesAndClampsInput) {
  const nudge::DeadzoneFilter filter(0.1);
  EXPECT_DOUBLE_EQ(filter.apply_axis(0.25), 0.25);
  EXPECT_DOUBLE_EQ(filter.apply_axis(-0.25), -0.25);
  EXPECT_DOUBLE_EQ(filter.apply_axis(2.0), 1.0);
  EXPECT_DOUBLE_EQ(filter.apply_axis(-2.0), -1.0);
}

TEST(DeadzoneFilter, RejectsInvalidDeadzone) {
  EXPECT_THROW(nudge::DeadzoneFilter(-0.01), std::invalid_argument);
  EXPECT_THROW(nudge::DeadzoneFilter(1.0), std::invalid_argument);
}
