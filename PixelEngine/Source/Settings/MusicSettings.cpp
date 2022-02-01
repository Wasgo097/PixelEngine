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
		try{
			json output;
			output["_mastervolume"] = _mastervolume;
			output["_musicvolume"] = _musicvolume;
			output["_effectvolume"] = _effectvolume;
			return output;
		}
		catch(...){
			return json();
		}
	}
	bool MusicSettings::JDeserialize(json json){
		try{
			_mastervolume = json["_mastervolume"];
			_musicvolume = json["_musicvolume"];
			_effectvolume = json["_effectvolume"];
			return true;
		}
		catch(...){
			return false;
		}
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