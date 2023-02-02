#include "config/config.h"

#include <toml.hpp>

namespace ACA
{

void Config::init(const std::string &filepath)
{
    auto data = toml::parse(filepath);
    const auto &logger = toml::find(data, "logger");
    m_logFilePath = toml::find<std::string>(logger, "file_path");
    m_minLogSeverity = toml::find<int>(logger, "log_severity");
}

} // namespace ACA