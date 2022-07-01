#pragma once
#include "SettingsBase.h"
namespace Settings{
	struct MusicSettings :public SettingsBase{
		MusicSettings(float master, float music, float effect) :master_vol{ master }, music_vol{ music }, effect_vol{ effect } {}
		MusicSettings() = default;
		virtual std::string ToStdString()const override;
		float master_vol = 0.0f;
		float music_vol = 0.0f;
		float effect_vol = 0.0f;

		auto operator <=>(const MusicSettings&)const = default;
	};
}