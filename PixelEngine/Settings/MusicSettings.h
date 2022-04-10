#pragma once
#include "SettingsBase.h"
namespace Settings{
	class MusicSettings :public SettingsBase{
	public:
		MusicSettings(float mastervolume, float musicvolume, float effectvolume) :_mastervolume(mastervolume), _musicvolume(musicvolume), _effectvolume(effectvolume) {}
		MusicSettings() = default;
	public:
		// Inherited via SettingsBase
		virtual std::string ToStdString()const override;
	public:
		float _mastervolume = 0.0f;
		float _musicvolume = 0.0f;
		float _effectvolume = 0.0f;
		bool operator ==(const MusicSettings& obj)const {
			return (_mastervolume == obj._mastervolume) &&
				(_musicvolume == obj._musicvolume) &&
				(_effectvolume == obj._effectvolume);
		}
	};
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(MusicSettings, _mastervolume, _musicvolume, _effectvolume)
}