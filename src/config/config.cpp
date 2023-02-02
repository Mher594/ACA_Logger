#include "config/config.h"

#include <filesystem>

#include <toml.hpp>

namespace ACA
{

void Config::init(const std::string &filepath)
{
    namespace fs = std::filesystem;
    const auto configFilePath = fs::path(filepath);
    if (!fs::exists(configFilePath))
    {
        return;
    }

    auto data = toml::parse(filepath);
    const auto &logger = toml::find(data, "logger");
    m_logPath = toml::find<std::string>(logger, "log_path");
    m_minLogSeverity = toml::find<int>(logger, "log_severity");
}

} // namespace ACA