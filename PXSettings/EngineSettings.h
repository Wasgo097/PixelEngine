#pragma once
#include "SettingsBase.h"
#include <compare>
namespace Settings {
	struct EngineSettings :public SettingsBase {
		EngineSettings(std::string window_settings, std::string music_settings, std::string world_settings) :
			window_settings_path{ window_settings }, music_settings_path{ music_settings }, world_settings_path{ world_settings }{}
		EngineSettings() = default;
		virtual std::string ToStdString()const override;
		std::string window_settings_path = "windowsettings.json";
		std::string music_settings_path = "musicsettings.json";
		std::string world_settings_path = "worldsettings.json";

		bool operator==(const EngineSettings& obj)const {
			return window_settings_path == obj.window_settings_path && music_settings_path == obj.music_settings_path && world_settings_path == obj.world_settings_path;
		}
	};
}