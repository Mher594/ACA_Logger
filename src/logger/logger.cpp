#include "logger/logger.h"

#include <filesystem>
#include <iomanip>
#include <mutex>
#include <thread>

#include <boost/date_time/posix_time/posix_time.hpp>

#include "config/config.h"

namespace
{

const std::string DefaultLogDirectory{"logs"};
const std::string DefaultLogFileName{"log.txt"};

constexpr int DefaultLogLevel{2}; // Level::Warning

} // namespace

namespace ACA
{

auto LevelToString(Level logLevel) -> std::string
{
    switch (logLevel)
    {
    case Level::Debug:
        return "Debug";
    case Level::Info:
        return "Info";
    case Level::Warning:
        return "Warning";
    case Level::Error:
        return "Error";
    case Level::Fatal:
        return "Fatal";
    }

    return {};
}

class Logger
{
  public:
    Logger() = default;
    Logger(const Logger &) = delete;
    Logger(Logger &&) = delete;
    auto operator=(const Logger &) -> Logger & = delete;
    auto operator=(Logger &&) -> Logger & = delete;
    ~Logger();

    void setLogPathAndOpen(const std::string &logPath);
    void setMinLogSeverity(int logSeverity);
    void addLog(Level logLevel, const std::string &msg);

  private:
    std::ofstream m_logfile;
    int m_loglevel{0};
    std::mutex m_fileMutex;
};

auto getLog() -> Logger *
{
    const static std::unique_ptr<Logger> slog = std::make_unique<Logger>();
    return slog.get();
}

void initLog(const Config &config)
{
    Logger *glog = getLog();
    glog->setLogPathAndOpen(config.getLogPath().value_or(DefaultLogDirectory));
    glog->setMinLogSeverity(config.getMinLogSeverity().value_or(DefaultLogLevel));
    glog->addLog(Level::Info, "Starting logging system.");
}

void log(Level logLevel, const std::string &msg)
{
    getLog()->addLog(logLevel, msg);
}

void Logger::setLogPathAndOpen(const std::string &logPath)
{
    namespace fs = std::filesystem;
    const auto pathToCreate = fs::path(logPath);
    if (!fs::exists(pathToCreate))
    {
        try
        {
            fs::create_directories(pathToCreate);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    const auto filePath = pathToCreate / fs::path(DefaultLogFileName);
    m_logfile.open(filePath.string());
}

void Logger::setMinLogSeverity(int logSeverity)
{
    m_loglevel = logSeverity;
}

void Logger::addLog(Level logLevel, const std::string &msg)
{
    if (static_cast<int>(logLevel) < m_loglevel)
    {
        return;
    }

    if (!m_logfile.is_open())
    {
        return;
    }

    const std::lock_guard<std::mutex> lock(m_fileMutex);
    using boost::posix_time::microsec_clock;
    using boost::posix_time::ptime;
    const ptime date_time = microsec_clock::universal_time();
    m_logfile << "Time: " << boost::posix_time::to_iso_extended_string(date_time) << ", thread #"
              << std::this_thread::get_id() << ", LogLevel: " << LevelToString(logLevel) << ", message: " << msg
              << std::endl;
}

Logger::~Logger()
{
    try
    {
        addLog(Level::Info, "Stopped logging system.");
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what();
    }
}

} // namespace ACA