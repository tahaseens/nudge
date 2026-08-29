#include "nudge_arbitration/authority_fsm.hpp"

#include <limits>
#include <stdexcept>

namespace nudge
{

AuthorityState AuthorityFsm::state() const noexcept { return state_; }

std::uint32_t AuthorityFsm::unresolved_disagreement_count() const noexcept
{
  return unresolved_disagreement_count_;
}

bool AuthorityFsm::transition_to(const AuthorityState requested) noexcept
{
  if (requested == state_) {
    return true;
  }

  const bool allowed =
      (state_ == AuthorityState::AUTONOMOUS && requested == AuthorityState::SHARED) ||
      (state_ == AuthorityState::SHARED && requested == AuthorityState::AUTONOMOUS) ||
      (state_ == AuthorityState::SHARED && requested == AuthorityState::HUMAN_DOMINANT) ||
      (state_ == AuthorityState::HUMAN_DOMINANT && requested == AuthorityState::SHARED);
  if (allowed) {
    state_ = requested;
  }
  return allowed;
}

bool AuthorityFsm::observe_unresolved_disagreement(const std::uint32_t repeat_limit)
{
  if (repeat_limit == 0U) {
    throw std::invalid_argument("repeat_limit must be configured above zero");
  }
  if (unresolved_disagreement_count_ < std::numeric_limits<std::uint32_t>::max()) {
    ++unresolved_disagreement_count_;
  }
  if (unresolved_disagreement_count_ >= repeat_limit) {
    state_ = AuthorityState::HUMAN_DOMINANT;
    return true;
  }
  return false;
}

void AuthorityFsm::clear_unresolved_disagreement() noexcept
{
  unresolved_disagreement_count_ = 0U;
}

}  // namespace nudge
