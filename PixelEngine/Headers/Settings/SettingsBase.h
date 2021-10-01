#pragma once
namespace Settings{
	class SettingsBase{
	public:
		virtual std::string ToStdString()const = 0;
	};
}