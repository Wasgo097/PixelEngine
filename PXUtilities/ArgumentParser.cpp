#include "pch.h"
#include "ArgumentParser.h"

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
