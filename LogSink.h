#pragma once

#include <string>
class LogSink
{
public:
	virtual void write(const std::string& message) = 0;
	virtual ~LogSink() = default;
};