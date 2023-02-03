#include "config/config.h"

#include <filesystem>

#include <toml.hpp>

namespace
{

const std::string ConfigLoggerTableKey{"logger"};
const std::string ConfigLoggerPathKey{"log_path"};
const std::string ConfigLoggerSeverityKey{"log_severity"};

} // namespace

namespace ACA
{

void Config::init(const std::string &filepath)
{
    namespace fs = std::filesystem;
    const auto configFilePath = fs::path(filepath);
    if (!fs::exists(configFilePath))
    {
        throw std::invalid_argument(std::string("File: ") + configFilePath.string() + std::string(" does not exists"));
    }

    const auto data = toml::parse(filepath);
    const auto &logger = toml::find(data, ConfigLoggerTableKey);

    if (logger.contains(ConfigLoggerPathKey))
    {
        m_logPath = toml::find<std::string>(logger, ConfigLoggerPathKey);
    }

    if (logger.contains(ConfigLoggerSeverityKey))
    {
        m_minLogSeverity = toml::find<int>(logger, ConfigLoggerSeverityKey);
    }
}

} // namespace ACA