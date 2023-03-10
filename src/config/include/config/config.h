#pragma once

#include <optional>
#include <string>

namespace ACA
{

class Config
{
  public:
    Config() = default;

    void init(const std::string &filepath);

    [[nodiscard]] auto getLogPath() const -> std::optional<std::string>
    {
        return m_logPath;
    }

    [[nodiscard]] auto getMinLogSeverity() const -> std::optional<int>
    {
        return m_minLogSeverity;
    }

  private:
    std::optional<std::string> m_logPath;
    std::optional<int> m_minLogSeverity{0};
};

} // namespace ACA
