#pragma once
namespace Settings {
	struct MusicSettings{
		MusicSettings(float master, float music, float effect) :master_vol{ master }, music_vol{ music }, effect_vol{ effect } {}
		MusicSettings() = default;

		bool operator==(const MusicSettings& obj)const {
			return master_vol == obj.master_vol && music_vol == obj.music_vol && effect_vol == obj.effect_vol;
		}

		float master_vol = 0.0f;
		float music_vol = 0.0f;
		float effect_vol = 0.0f;
	};
}