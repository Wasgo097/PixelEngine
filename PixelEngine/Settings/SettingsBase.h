#pragma once
#include <string>
#include "Utility/json.hpp"
using nlohmann::json;
namespace Settings{
	class SettingsBase{
	public:
		virtual std::string ToStdString()const = 0;
	};
}