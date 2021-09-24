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
			return "Master volume "+std::to_string(_mastervolume)+" Music Volume: "+std::to_string(_musicvolume)+" Effect Volume "+std::to_string(_effectvolume);
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