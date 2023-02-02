#include "logger/logger.h"

#include <boost/date_time/posix_time/posix_time.hpp>

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
        return;
    }

    if (!m_logfile.is_open())
    {
        return;
    }

    using boost::posix_time::microsec_clock;
    using boost::posix_time::ptime;
    const ptime date_time = microsec_clock::universal_time();
    m_logfile << boost::posix_time::to_iso_extended_string(date_time) << ", " << LevelToString(logLevel) << ": " << msg
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
        std::cout << e.what();
    }
    catch (...)
    {
        std::cout << "Default Exception";
    }
}

} // namespace ACA