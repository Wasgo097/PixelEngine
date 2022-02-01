#pragma once
#include "SettingsBase.h"
#include "Utility/ISerializable.h"
using nlohmann::json;
namespace Settings{
	class MusicSettings :public SettingsBase, Utility::IJsonSerializable{
	public:
		MusicSettings(float mastervolume, float musicvolume, float effectvolume);
		MusicSettings() = default;
	public:
		// Inherited via SettingsBase
		virtual std::string ToStdString()const override;
		// Inherited via IJsonSerializable
		virtual json JSerialize() const override;
		virtual bool JDeserialize(json json) override;
	public:
		float  MasterVolume()const;
		float  MusicVolume()const;
		float  EffectVolume()const;
	protected:
		float _mastervolume = 0.0f;
		float _musicvolume = 0.0f;
		float _effectvolume = 0.0f;
	};
}