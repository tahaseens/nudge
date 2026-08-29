#include <gtest/gtest.h>

#include <rclcpp/serialization.hpp>
#include <rclcpp/serialized_message.hpp>

#include "nudge_interfaces/msg/correction_interpretation.hpp"

TEST(NudgeInterfaces, CorrectionInterpretationRoundTrip) {
  nudge_interfaces::msg::CorrectionInterpretation original;
  original.correction_type = original.CORRECTION_PLAN;
  original.confidence = 0.625F;
  original.interpretation_source = original.SOURCE_HEURISTIC;
  original.matched_heuristic_rule_id = 4U;
  original.source_event.event_id = "event-001";
  original.source_event.operator_context = original.source_event.OPERATOR_REMOTE;

  rclcpp::Serialization<nudge_interfaces::msg::CorrectionInterpretation> serializer;
  rclcpp::SerializedMessage bytes;
  serializer.serialize_message(&original, &bytes);

  nudge_interfaces::msg::CorrectionInterpretation restored;
  serializer.deserialize_message(&bytes, &restored);

  EXPECT_EQ(restored.correction_type, restored.CORRECTION_PLAN);
  EXPECT_FLOAT_EQ(restored.confidence, 0.625F);
  EXPECT_EQ(restored.interpretation_source, restored.SOURCE_HEURISTIC);
  EXPECT_EQ(restored.matched_heuristic_rule_id, 4U);
  EXPECT_EQ(restored.source_event.event_id, "event-001");
  EXPECT_EQ(restored.source_event.operator_context, restored.source_event.OPERATOR_REMOTE);
}

TEST(NudgeInterfaces, StableCorrectionTypeValues) {
  nudge_interfaces::msg::CorrectionInterpretation message;
  EXPECT_EQ(message.CORRECTION_UNKNOWN, 0U);
  EXPECT_EQ(message.CORRECTION_MOTION, 1U);
  EXPECT_EQ(message.CORRECTION_PLAN, 2U);
  EXPECT_EQ(message.CORRECTION_GOAL, 3U);
  EXPECT_EQ(message.CORRECTION_AUTHORITY, 4U);
}
