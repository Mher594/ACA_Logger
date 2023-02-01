#pragma once

#include <fstream>
#include <memory>
#include <string>

namespace ACA
{

// Severity level enum.
enum class Level
{
    Debug,
    Info,
    Warning,
    Error,
    Fatal
};

class Config;

void initLog(const Config &config);

void log(Level logLevel, const std::string &msg);

} // namespace ACA