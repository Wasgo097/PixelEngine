#include "pch.h"
#include "FileLogger.h"
namespace Log {
	FileLogger::FileLogger(const std::string& file_path) :_f_stream(file_path, std::ofstream::app) {
		if (!_f_stream.is_open())
			throw std::invalid_argument("Wrong FileLogger path");
	}
	FileLogger::~FileLogger() {
		_f_stream.close();
	}
	void FileLogger::Log(const std::string& to_log) {
		_s_stream << to_log << std::endl;
	}
	void FileLogger::FLush() {
		_f_stream << _s_stream.str() << std::endl;
		_s_stream.clear();
	}
}