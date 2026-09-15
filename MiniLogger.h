// MiniLogger.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#pragma once

#include <iostream>
#include <string>
#include<fstream>
#include <sstream>
#include <memory>
#include <vector>
#include "LogSink.h"
#include <mutex>
#include <queue>
#include <thread>
#include <condition_variable>

enum class LogLevel
{
	DEBUG = 0,
	INFO = 1,
	WARNING = 2,
	ERROR = 3

};

class Logger
{
private:
	std::string getCurrentTime();

	std::string levelToString(LogLevel level);

	void writeLog(LogLevel level,
		const std::string& message);

	std::mutex mutex_;

	std::vector<std::shared_ptr<LogSink>> sinks;

	std::queue<std::string> logQueue;
	std::mutex queueMutex;
	std::thread workerThread;
	std::condition_variable cv;
	bool stop = false;
	void workerLoop();

	LogLevel minLevel;
	
	template <typename... Args>
	std::string makeMessage(Args... args)
	{
		std::ostringstream oss;
		(oss << ... << args);
		return oss.str();
	}

	

public:
	Logger(LogLevel minLevel = LogLevel::INFO);

	~Logger();

	void removeSink(size_t index);

	void addSink(std::shared_ptr<LogSink> sink);

	template <typename... Args>
	void info(Args... args)
	{
		writeLog(LogLevel::INFO, makeMessage(args...));
	}

	template <typename... Args>
	void warning(Args... args)
	{
		writeLog(LogLevel::WARNING, makeMessage(args...));
	}

	template <typename... Args>
	void error(Args... args)
	{
		writeLog(LogLevel::ERROR, makeMessage(args...));
	}

	template <typename... Args>
	void debug(Args... args)
	{
		writeLog(LogLevel::DEBUG, makeMessage(args...));
	}
};


// TODO: 在此处引用程序需要的其他标头。
