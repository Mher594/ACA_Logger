#pragma once

#include <string>

namespace ACA
{

class Config
{
  public:
    Config() = default;

    void init(const std::string &filepath);

    [[nodiscard]] auto getLogPath() const -> std::string
    {
        return m_logPath;
    }

    [[nodiscard]] auto getMinLogSeverity() const -> int
    {
        return m_minLogSeverity;
    }

  private:
    std::string m_logPath;
    int m_minLogSeverity{0};
};

} // namespace ACA
