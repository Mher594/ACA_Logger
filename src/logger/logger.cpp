#include "logger/logger.h"

#include <chrono>

#include "config/config.h"

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

    void setFilePathAndOpen(const std::string &filepath);
    void setMinLogSeverity(int logSeverity);
    void addLog(Level logLevel, const std::string &msg);

  private:
    std::ofstream m_logfile;
    int m_loglevel{0};
};

auto getLog() -> Logger *
{
    const static std::unique_ptr<Logger> slog = std::make_unique<Logger>();
    return slog.get();
}

void initLog(const Config &config)
{
    Logger *glog = getLog();
    glog->setFilePathAndOpen(config.getLogFilePath());
    glog->setMinLogSeverity(config.getMinLogSeverity());
    glog->addLog(Level::Info, "Starting logging system.");
}

void log(Level logLevel, const std::string &msg)
{
    getLog()->addLog(logLevel, msg);
}

void Logger::setFilePathAndOpen(const std::string &filepath)
{
    m_logfile.open(filepath);
}

void Logger::setMinLogSeverity(int logSeverity)
{
    m_loglevel = logSeverity;
}

void Logger::addLog(Level logLevel, const std::string &msg)
{
    if (static_cast<int>(logLevel) >= m_loglevel)
    {
        if (m_logfile.is_open())
        {
            using std::chrono::system_clock;
            using std::chrono::zoned_time;
            auto local = zoned_time{std::chrono::current_zone(), system_clock::now()};
            m_logfile << local << ", " << LevelToString(logLevel) << ": " << msg << std::endl;
        }
    }
}

Logger::~Logger()
{
    addLog(Level::Info, "Stopped logging system.");
}

} // namespace ACA