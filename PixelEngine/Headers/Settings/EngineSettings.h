#pragma once
#include "SettingsBase.h"
namespace Settings {
	struct EngineSettings :public SettingsBase{
	public:
		EngineSettings(std::string winsettings, std::string mussettings, std::string worldsettings):
			_windowsettings(winsettings),_musicsettings(mussettings),_worldsettings(worldsettings){}
		EngineSettings() = default;
	public:
		// Inherited via SettingsBase
		virtual std::string ToStdString()const override;
	public:
		std::string _windowsettings = "window.json";
		std::string _musicsettings = "music.json";
		std::string _worldsettings = "world.json";
	};
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(EngineSettings, _windowsettings, _musicsettings, _worldsettings)
}