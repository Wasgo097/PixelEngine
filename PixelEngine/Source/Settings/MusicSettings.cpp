#include "Settings/MusicSettings.h"
#include <sstream>
namespace Settings{
	MusicSettings::MusicSettings(float mastervolume, float musicvolume, float effectvolume) :
		_mastervolume(mastervolume), _musicvolume(musicvolume), _effectvolume(effectvolume){}

	std::string MusicSettings::ToStdString() const{
		std::stringstream stream;
		stream << "Master volume " << _mastervolume << " Music Volume: " << _musicvolume << " Effect Volume " << _effectvolume;
		return stream.str();
	}
	json MusicSettings::JSerialize() const{
		return json();
	}
	bool MusicSettings::JDeserialize(json json){
		return false;
	}
	float MusicSettings::MasterVolume() const{
		return _mastervolume;
	}
	float MusicSettings::MusicVolume() const{
		return _musicvolume;
	}
	float MusicSettings::EffectVolume() const{
		return _effectvolume;
	}
}