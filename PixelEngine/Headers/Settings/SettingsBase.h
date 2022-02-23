#pragma once
#include <string>
#include "json.hpp"
using nlohmann::json;
namespace Settings{
	struct SettingsBase{
		virtual std::string ToStdString()const = 0;
	};
}