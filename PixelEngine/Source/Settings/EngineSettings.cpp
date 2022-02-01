#include "Settings/EngineSettings.h"
#include <sstream>
namespace Settings{
	EngineSettings::EngineSettings(std::string rootpath,std::string winsettings, std::string mussettings, std::string worldsettings) :
		_rootpath(rootpath),_windowsettings(winsettings), _musicsettings(mussettings), _worldsettings(worldsettings){}

	inline std::string EngineSettings::ToStdString() const{
		std::stringstream stream;
		stream << "Rootpath: "<<_rootpath<< " Window settings: " << _windowsettings << " World Settings: " << _worldsettings << " Music Settings: " << _musicsettings;
		return stream.str();
	}
	json EngineSettings::JSerialize() const{
		return json();
	}
	bool EngineSettings::JDeserialize(json json){
		return false;
	}
	const std::string & EngineSettings::WindowSettings() const{
		return _windowsettings;
	}
	const std::string & EngineSettings::MusicSettings() const{
		return _musicsettings;
	}
	const std::string & EngineSettings::WorldSettings() const{
		return _worldsettings;
	}
}