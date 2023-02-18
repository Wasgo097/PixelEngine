#pragma once
#include <string>
namespace Log {
	class ILogger {
	public:
		virtual ~ILogger() = default;
		virtual void Log(const std::string& to_log)=0;
	};
}