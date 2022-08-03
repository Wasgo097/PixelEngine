#pragma once
#include "PXUtilities/Interfaces/ILogger.h"
#include <fstream>
#include <sstream>
namespace Log {
	class FileLogger :public ILogger {
	public:
		FileLogger(const std::string& file_path);
		virtual ~FileLogger();
		// Inherited via ILogger
		virtual void Log(const std::string& to_log) override;
		virtual void FLush() override;
	protected:
		std::stringstream _s_stream;
		std::ofstream _f_stream;
	};
}