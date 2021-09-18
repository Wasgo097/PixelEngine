#pragma once
namespace Settings{
	class MusicSettings{
	public:
		MusicSettings(double mastervolume,double musicvolume,double effectvolume):
			_mastervolume(mastervolume),_musicvolume(musicvolume),_effectvolume(effectvolume){}
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