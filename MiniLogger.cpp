#include "MiniLogger.h"
#include <ctime>
#include <iomanip>

void Logger::addSink(std::shared_ptr<LogSink> sink)
{
    std::lock_guard<std::mutex> lock(mutex_);
    sinks.push_back(sink);
}

void Logger::removeSink(size_t index)
{
    std::lock_guard<std::mutex> lock(mutex_);

    if (index >= sinks.size())
    {
        return;
    }

    sinks.erase(sinks.begin() + index);
}

void Logger::workerLoop()
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(queueMutex);

        cv.wait(lock, [this]()
            {
                return !logQueue.empty() || stop;
            });


        if (stop && logQueue.empty())
        {
            break;
        }

        std::string message = logQueue.front();
        logQueue.pop();

        lock.unlock();

        std::vector<std::shared_ptr<LogSink>> localsinks;
        
        {
            std::lock_guard<std::mutex> sinkLock(mutex_);
            localsinks = sinks;
        }

        for (const auto& sink : sinks)
        {
            sink->write(message);
        }
    }
}

void Logger::writeLog(LogLevel level,
    const std::string& message)
{
    std::lock_guard<std::mutex> lock(mutex_);

    if (static_cast<int>(level) <
        static_cast<int>(minLevel))
    {
        return;
    }
    std::string logMessage =
        "[" + getCurrentTime() + "] "
        "[" + levelToString(level) + "] "
        + message;

    {
        std::lock_guard<std::mutex> lock(queueMutex);

        logQueue.push(logMessage);
    }

    cv.notify_one();
}

Logger::Logger(LogLevel minLevel)
    : minLevel(minLevel)
{
    workerThread = std::thread(&Logger::workerLoop, this);
}

Logger::~Logger()
{
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        stop = true;
    }
    cv.notify_one();
    
    if (workerThread.joinable())
    {
        workerThread.join();
    }
}

std::string Logger::getCurrentTime()
{
    std::time_t now = std::time(nullptr);
    std::tm timeInfo{};
    localtime_s(&timeInfo, &now);
    std::ostringstream oss;
    oss << std::put_time(&timeInfo, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

std::string Logger::levelToString(LogLevel level)
{
    switch (level)
    {
    case LogLevel::DEBUG:
        return "DEBUG";
    case LogLevel::INFO:
        return "INFO";
    case LogLevel::WARNING:
        return "WARNING";
    case LogLevel::ERROR:
        return "ERROR";
    default:
        return "UNKNOWM";
    }
}
