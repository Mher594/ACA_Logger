#pragma once

#include <string>

namespace ACA
{

class Config
{
  public:
    Config() = default;

    void init(const std::string &filepath);

    [[nodiscard]] auto getLogFilePath() const -> std::string
    {
        return m_logFilePath;
    }

    [[nodiscard]] auto getMinLogSeverity() const -> int
    {
        return m_minLogSeverity;
    }

  private:
    std::string m_logFilePath;
    int m_minLogSeverity{0};
};

} // namespace ACA
