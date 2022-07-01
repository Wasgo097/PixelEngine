#pragma once
#include <string>
#include <compare>
namespace Settings {
	struct SettingsBase {
	public:
		virtual std::string ToStdString()const = 0;
		virtual ~SettingsBase() = default;
	};
}