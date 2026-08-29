#pragma once

#include <cstdint>

namespace nudge
{

enum class LifecycleState : std::uint8_t
{
  INIT = 0,
  READY = 1,
  RUNNING = 2,
  PAUSED = 3,
  COMPLETE = 4,
  ESTOP = 5,
};

class LifecycleFsm
{
public:
  [[nodiscard]] LifecycleState state() const noexcept;
  bool transition_to(LifecycleState requested) noexcept;
  void emergency_stop() noexcept;

private:
  LifecycleState state_{LifecycleState::INIT};
};

}  // namespace nudge
