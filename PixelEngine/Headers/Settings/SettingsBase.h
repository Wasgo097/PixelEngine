#pragma once
#include <string>
namespace Settings{
	class SettingsBase{
	public:
		virtual std::string ToStdString()const = 0;
	};
}