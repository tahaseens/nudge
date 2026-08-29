#pragma once

namespace nudge
{

class DeadzoneFilter
{
public:
  explicit DeadzoneFilter(double deadzone);

  [[nodiscard]] double apply_axis(double value) const noexcept;
  [[nodiscard]] double deadzone() const noexcept;

private:
  double deadzone_;
};

}  // namespace nudge
