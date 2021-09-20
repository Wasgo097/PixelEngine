#pragma once
#include "SettingsBase.h"
namespace Settings{
	class EngineSettings:public SettingsBase{
	public:
		EngineSettings(std::string winsettings, std::string mussettings, std::string worldsettings) :
			_windowsettings(winsettings), _musicsettings(mussettings), _worldsettings(worldsettings){}
		EngineSettings() = default;
		// Inherited via SettingsBase
		inline virtual std::string ToStdString() override{
			return "Window settings: "+_windowsettings + " World Settings: " + _worldsettings + " Music Settings: " + _musicsettings;
		}
		inline const std::string & WindowSettings()const{
			return _windowsettings;
		}
		inline const std::string & MusicSettings()const{
			return _musicsettings;
		}
		inline const std::string & WorldSettings()const{
			return _worldsettings;
		}
	protected:
		std::string _windowsettings;
		std::string _musicsettings;
		std::string _worldsettings;

	};
}