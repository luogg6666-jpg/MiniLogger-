#pragma once

#include "LogSink.h"
#include <fstream>
#include <mutex>

class FileSink :public LogSink
{
private:
	std::ofstream file;
	std::mutex mutex_;
public:
	FileSink(const std::string& filename)
	{
		file.open(filename, std::ios::app);
	}
	void write(const std::string& message) override
	{
		std::lock_guard<std::mutex> lock(mutex_);

		if (file.is_open())
		{
			file << message << std::endl;
		}
	}
};