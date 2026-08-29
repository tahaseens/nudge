#pragma once

#include <cstdint>

namespace nudge
{

enum class AuthorityState : std::uint8_t
{
  AUTONOMOUS = 0,
  SHARED = 1,
  HUMAN_DOMINANT = 2,
};

class AuthorityFsm
{
public:
  [[nodiscard]] AuthorityState state() const noexcept;
  [[nodiscard]] std::uint32_t unresolved_disagreement_count() const noexcept;

  bool transition_to(AuthorityState requested) noexcept;
  bool observe_unresolved_disagreement(std::uint32_t repeat_limit);
  void clear_unresolved_disagreement() noexcept;

private:
  AuthorityState state_{AuthorityState::AUTONOMOUS};
  std::uint32_t unresolved_disagreement_count_{0};
};

}  // namespace nudge
