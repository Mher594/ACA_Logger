#pragma once

#include <string_view>

namespace ACA
{

class Config
{
  public:
    Config() = default;

    void init(std::string_view filepath);

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
