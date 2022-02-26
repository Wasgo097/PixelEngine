#pragma once
#include "SettingsBase.h"
#include <compare>
namespace Settings {
	class EngineSettings :public SettingsBase{
	public:
		EngineSettings(std::string winsettings, std::string mussettings, std::string worldsettings):
			_windowsettings(winsettings),_musicsettings(mussettings),_worldsettings(worldsettings){}
		EngineSettings() = default;
	public:
		// Inherited via SettingsBase
		virtual std::string ToStdString()const override;
	public:
		std::string _windowsettings = "windowsettings.json";
		std::string _musicsettings = "musicsettings.json";
		std::string _worldsettings = "worldsettings.json";
		bool operator ==(const EngineSettings& obj)const {
			return (_windowsettings == obj._windowsettings) &&
				(_musicsettings == obj._musicsettings) &&
				(_worldsettings == obj._worldsettings);
		}
	};
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(EngineSettings, _windowsettings, _musicsettings, _worldsettings)
}