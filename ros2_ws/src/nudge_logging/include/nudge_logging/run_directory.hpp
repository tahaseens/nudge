#pragma once

#include <filesystem>
#include <string>

namespace nudge
{

class RunDirectory
{
public:
  [[nodiscard]] static std::filesystem::path create(const std::filesystem::path& runs_root,
                                                    const std::string& timestamp,
                                                    const std::string& scenario_id);
};

}  // namespace nudge
