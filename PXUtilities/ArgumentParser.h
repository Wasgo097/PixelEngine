#pragma once
#include <unordered_map>
#include <string>
#include <concepts>
#include <optional>
class ArgumentParser {
public:
	bool AddNewArgument(const std::string& key, const std::string& value);
	std::optional<std::string> GetRowValue(const std::string& key)const;
	template<typename T>
		requires std::is_fundamental_v<T>
	std::optional<T> GetValue(const std::string& key)const {
		if (_arguments.contains(key)) {
			std::istringstream ss(_arguments.at(key));
			T num;
			ss >> num;
			return num;
		}
		return {};
	}

protected:
	std::unordered_map <std::string, std::string> _arguments;
};