#pragma once
#include "PXUtilities/Interfaces/ILogger.h"
namespace Log {
	class ConsoleLogger :public ILogger {
	public:
		// Inherited via ILogger
		virtual void Log(const std::string& to_log) override;
	};
}