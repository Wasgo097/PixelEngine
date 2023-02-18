#include "pch.h"
#include "ConsoleLogger.h"
#include <iostream>
namespace Log {
	void ConsoleLogger::Log(const std::string& to_log) {
		std::cout << to_log << std::endl;
	}
}