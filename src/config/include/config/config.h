#pragma once

#include <string>

namespace ACA
{

class Config
{
  public:
    Config() = default;

    void init(const std::string &filepath);

    [[nodiscard]] std::string getLogFilePath() const;
    [[nodiscard]] int getMinLogSeverity() const;

  private:
    std::string m_logFilePath;
    int m_minLogSeverity{0};
};

} // namespace ACA
