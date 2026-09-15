#pragma once

#include "LogSink.h"
#include <iostream>

class ConsoleSink : public LogSink
{
public:
	void write(const std::string& message) override
	{
		std::cout << message << std::endl;
	}
};
