#pragma once
#include <string>
namespace Settings{
	struct SettingsBase{
	public:
		virtual std::string ToStdString()const = 0;
		virtual ~SettingsBase() = default;
	};
}