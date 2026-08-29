#include <gtest/gtest.h>

#include "nudge_arbitration/lifecycle_fsm.hpp"

TEST(LifecycleFsm, NominalRunAndPauseTransitions) {
  nudge::LifecycleFsm fsm;
  EXPECT_TRUE(fsm.transition_to(nudge::LifecycleState::READY));
  EXPECT_TRUE(fsm.transition_to(nudge::LifecycleState::RUNNING));
  EXPECT_TRUE(fsm.transition_to(nudge::LifecycleState::PAUSED));
  EXPECT_TRUE(fsm.transition_to(nudge::LifecycleState::RUNNING));
  EXPECT_TRUE(fsm.transition_to(nudge::LifecycleState::COMPLETE));
}

TEST(LifecycleFsm, RejectsUnspecifiedResetAndSkipTransitions) {
  nudge::LifecycleFsm fsm;
  EXPECT_FALSE(fsm.transition_to(nudge::LifecycleState::RUNNING));
  fsm.emergency_stop();
  EXPECT_FALSE(fsm.transition_to(nudge::LifecycleState::INIT));
  EXPECT_EQ(fsm.state(), nudge::LifecycleState::ESTOP);
}

TEST(LifecycleFsm, EmergencyStopIsReachableFromNominalStates) {
  nudge::LifecycleFsm fsm;
  ASSERT_TRUE(fsm.transition_to(nudge::LifecycleState::READY));
  EXPECT_TRUE(fsm.transition_to(nudge::LifecycleState::ESTOP));
  EXPECT_EQ(fsm.state(), nudge::LifecycleState::ESTOP);
}
