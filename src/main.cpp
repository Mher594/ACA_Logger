#include "config/config.h"
#include "logger/logger.h"

using namespace ACA;

int main()
{
    Config obj;
    obj.init("D:/Workspace/ACA_Logger/logger.toml");

    initLog(obj);
    log(Level::Debug, "random log 1");
    log(Level::Info, "random log 2");
    log(Level::Warning, "random log 3");
    log(Level::Error, "random log 4");
    log(Level::Fatal, "random log 5");

    return 0;
}