#pragma once
#include "SettingsBase.h"
namespace Settings{
	class EngineSettings:public SettingsBase{
	public:
		EngineSettings(std::string winsettings, std::string mussettings, std::string worldsettings) :
			_windowsettings(winsettings), _musicsettings(mussettings), _worldsettings(worldsettings){}
		EngineSettings() = default;
		// Inherited via SettingsBase
		virtual std::string ToStdString() override{
			std::stringstream stream;
			stream<< "Window settings: "<<_windowsettings << " World Settings: " << _worldsettings << " Music Settings: " << _musicsettings;
			return stream.str();
		}
		const std::string & WindowSettings()const{
			return _windowsettings;
		}
		const std::string & MusicSettings()const{
			return _musicsettings;
		}
		const std::string & WorldSettings()const{
			return _worldsettings;
		}
	protected:
		std::string _windowsettings="";
		std::string _musicsettings = "";
		std::string _worldsettings = "";
	};
}