#include "config/config.h"
#include "logger/logger.h"

auto main() -> int
{
    ACA::Config obj;
    obj.init("D:/Workspace/ACA_Logger/logger.toml");

    ACA::initLog(obj);
    ACA::log(ACA::Level::Debug, "random log 1");
    ACA::log(ACA::Level::Info, "random log 2");
    ACA::log(ACA::Level::Warning, "random log 3");
    ACA::log(ACA::Level::Error, "random log 4");
    ACA::log(ACA::Level::Fatal, "random log 5");

    return 0;
}