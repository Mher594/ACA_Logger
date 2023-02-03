#pragma once

#include <fstream>
#include <memory>
#include <string>

namespace ACA
{

// Severity level enum.
enum class Level
{
    Debug = 0,
    Info = 1,
    Warning = 2,
    Error = 3,
    Fatal = 4
};

class Config;

void initLog(const Config &config);

void log(Level logLevel, const std::string &msg);

} // namespace ACA