#include "nudge_arbitration/lifecycle_fsm.hpp"

namespace nudge
{

LifecycleState LifecycleFsm::state() const noexcept { return state_; }

bool LifecycleFsm::transition_to(const LifecycleState requested) noexcept
{
  if (requested == state_) {
    return true;
  }
  if (requested == LifecycleState::ESTOP) {
    state_ = requested;
    return true;
  }
  if (state_ == LifecycleState::ESTOP || state_ == LifecycleState::COMPLETE) {
    return false;
  }

  const bool allowed =
      (state_ == LifecycleState::INIT && requested == LifecycleState::READY) ||
      (state_ == LifecycleState::READY && requested == LifecycleState::RUNNING) ||
      (state_ == LifecycleState::RUNNING && requested == LifecycleState::PAUSED) ||
      (state_ == LifecycleState::PAUSED && requested == LifecycleState::RUNNING) ||
      (state_ == LifecycleState::RUNNING && requested == LifecycleState::COMPLETE);
  if (allowed) {
    state_ = requested;
  }
  return allowed;
}

void LifecycleFsm::emergency_stop() noexcept { state_ = LifecycleState::ESTOP; }

}  // namespace nudge
