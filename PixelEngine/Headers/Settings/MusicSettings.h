#pragma once
#include "SettingsBase.h"
namespace Settings{
	class MusicSettings :public SettingsBase{
	public:
		MusicSettings(double mastervolume,double musicvolume,double effectvolume):
			_mastervolume(mastervolume),_musicvolume(musicvolume),_effectvolume(effectvolume){}
		MusicSettings() = default;
		// Inherited via SettingsBase
		inline virtual std::string ToStdString() override{
			return "Master volume "+std::to_string(_mastervolume)+" Music Volume: "+std::to_string(_musicvolume)+" Effect Volume "+std::to_string(_effectvolume);
		}
		const double & MasterVolume()const{
			return _mastervolume;
		}
		const double & MusicVolume()const{
			return _musicvolume;
		}
		const double& EffectVolume()const{
			return _effectvolume;
		}
	protected:
		double _mastervolume;
		double _musicvolume;
		double _effectvolume;
	};
}