#pragma once
#include "SettingsBase.h"
namespace Settings{
	class MusicSettings :public SettingsBase{
	public:
		MusicSettings(float mastervolume,float musicvolume,float effectvolume):
			_mastervolume(mastervolume),_musicvolume(musicvolume),_effectvolume(effectvolume){}
		MusicSettings() = default;
		// Inherited via SettingsBase
		inline virtual std::string ToStdString() override{
			std::stringstream stream;
			stream<< "Master volume "<<_mastervolume<<" Music Volume: "<<_musicvolume<<" Effect Volume "<<_effectvolume;
			return stream.str();
		}
		const float & MasterVolume()const{
			return _mastervolume;
		}
		const float & MusicVolume()const{
			return _musicvolume;
		}
		const float& EffectVolume()const{
			return _effectvolume;
		}
	protected:
		float _mastervolume=0.0f;
		float _musicvolume = 0.0f;
		float _effectvolume = 0.0f;
	};
}