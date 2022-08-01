#include "pch.h"
#include "ArgumentParser.h"

ArgumentParser::ArgumentParser(int argc, const char* argv[]) {
	if (argc < 3 or (argc - 1) % 2 != 0)
		throw std::invalid_argument("Wrong count of arguments in ArgumentParser constructor");
	for (int i = 1; i < argc; i+=2) {
		AddNewArgument(argv[i], argv[i+1]);
	}
}

bool ArgumentParser::AddNewArgument(const std::string& key, const std::string& value) {
	if (!_arguments.contains(key)) {
		_arguments.insert(std::make_pair(key, value));
		return true;
	}
	else
		return false;
}

std::optional<std::string> ArgumentParser::GetRowValue(const std::string& key) const {
	if (_arguments.contains(key))
		return _arguments.at(key);
	return {};
}
