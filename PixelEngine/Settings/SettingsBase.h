#pragma once
#include <string>
#include "Utility/json.hpp"
#include <compare>
using nlohmann::json;
namespace Settings{
	class SettingsBase{
	public:
		virtual std::string ToStdString()const = 0;
		virtual ~SettingsBase() = default;
	};
}