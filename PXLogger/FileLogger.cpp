#include "pch.h"
#include "FileLogger.h"
namespace Log {
	FileLogger::FileLogger(const std::string& file_path) :_f_stream(file_path, std::ofstream::app) {
	}
	FileLogger::~FileLogger() {
		_f_stream.close();
	}
	void FileLogger::Log(const std::string& to_log) {
		_s_stream << to_log << std::endl;
	}
}