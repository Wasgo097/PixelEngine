#pragma once
#include "PXUtilities/Interfaces/ILogger.h"
#include <sstream>
namespace Log {
	class ConsoleLogger :public ILogger {
	public:
		// Inherited via ILogger
		virtual void Log(const std::string& to_log) override;
		virtual void FLush() override;
	protected:
		std::stringstream _stream;
	};
}