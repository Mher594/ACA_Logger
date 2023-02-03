#include <iostream>
#include <thread>

#include "config/config.h"
#include "logger/logger.h"

namespace
{

const std::string ConfigFilePath{"logger.toml"};

}

auto main() -> int
{
    ACA::Config obj;
    obj.init(ConfigFilePath);

    ACA::initLog(obj);

    std::cout << "start loigging...\n";

    ACA::log(ACA::Level::Debug, "random log 1");
    ACA::log(ACA::Level::Info, "random log 2");
    ACA::log(ACA::Level::Warning, "random log 3");
    ACA::log(ACA::Level::Error, "random log 4");
    ACA::log(ACA::Level::Fatal, "random log 5");

    std::thread thread_1(ACA::log, ACA::Level::Error, "random log 4");
    std::thread thread_2(ACA::log, ACA::Level::Fatal, "random log 5");

    try
    {
        thread_1.join();
        thread_2.join();
    }
    catch (const std::system_error &e)
    {
        std::cout << "Caught system_error with code " << e.code() << " meaning " << e.what() << '\n';
    }

    std::cout << "stop loigging...\n";

    return 0;
}