#include "pch.h"
#include "ConsoleLogger.h"
#include <iostream>
namespace Log {
	void ConsoleLogger::Log(const std::string& to_log) {
		_stream << to_log << std::endl;
	}
	void ConsoleLogger::FLush()	{
		std::cout << _stream.str();
		_stream.clear();
	}
}