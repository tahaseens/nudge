#include <gtest/gtest.h>

#include "nudge_arbitration/authority_fsm.hpp"

TEST(AuthorityFsm, AcceptsValidAdjacentTransitions) {
  nudge::AuthorityFsm fsm;
  EXPECT_TRUE(fsm.transition_to(nudge::AuthorityState::SHARED));
  EXPECT_TRUE(fsm.transition_to(nudge::AuthorityState::HUMAN_DOMINANT));
  EXPECT_TRUE(fsm.transition_to(nudge::AuthorityState::SHARED));
  EXPECT_TRUE(fsm.transition_to(nudge::AuthorityState::AUTONOMOUS));
}

TEST(AuthorityFsm, RejectsInvalidTransitions) {
  nudge::AuthorityFsm fsm;
  EXPECT_FALSE(fsm.transition_to(nudge::AuthorityState::HUMAN_DOMINANT));
  EXPECT_EQ(fsm.state(), nudge::AuthorityState::AUTONOMOUS);
  ASSERT_TRUE(fsm.transition_to(nudge::AuthorityState::SHARED));
  ASSERT_TRUE(fsm.transition_to(nudge::AuthorityState::HUMAN_DOMINANT));
  EXPECT_FALSE(fsm.transition_to(nudge::AuthorityState::AUTONOMOUS));
  EXPECT_EQ(fsm.state(), nudge::AuthorityState::HUMAN_DOMINANT);
}

TEST(AuthorityFsm, RecoveryPassesThroughShared) {
  nudge::AuthorityFsm fsm;
  ASSERT_TRUE(fsm.transition_to(nudge::AuthorityState::SHARED));
  ASSERT_TRUE(fsm.transition_to(nudge::AuthorityState::HUMAN_DOMINANT));
  EXPECT_FALSE(fsm.transition_to(nudge::AuthorityState::AUTONOMOUS));
  EXPECT_TRUE(fsm.transition_to(nudge::AuthorityState::SHARED));
  EXPECT_TRUE(fsm.transition_to(nudge::AuthorityState::AUTONOMOUS));
}

TEST(AuthorityFsm, RepeatedDisagreementForcesHumanDominant) {
  nudge::AuthorityFsm fsm;
  EXPECT_FALSE(fsm.observe_unresolved_disagreement(3U));
  EXPECT_FALSE(fsm.observe_unresolved_disagreement(3U));
  EXPECT_TRUE(fsm.observe_unresolved_disagreement(3U));
  EXPECT_EQ(fsm.state(), nudge::AuthorityState::HUMAN_DOMINANT);
}
