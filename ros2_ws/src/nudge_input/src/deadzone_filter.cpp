#include "nudge_input/deadzone_filter.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace nudge
{

DeadzoneFilter::DeadzoneFilter(const double deadzone) : deadzone_(deadzone)
{
  if (deadzone < 0.0 || deadzone >= 1.0) {
    throw std::invalid_argument("deadzone must be in [0, 1)");
  }
}

double DeadzoneFilter::apply_axis(const double value) const noexcept
{
  const double clamped = std::max(-1.0, std::min(value, 1.0));
  return std::abs(clamped) <= deadzone_ ? 0.0 : clamped;
}

double DeadzoneFilter::deadzone() const noexcept { return deadzone_; }

}  // namespace nudge
