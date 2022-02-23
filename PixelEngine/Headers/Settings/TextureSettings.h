#pragma once
#include"SettingsBase.h"
namespace Settings{
	struct TextureSettings:public SettingsBase{
	public:
		TextureSettings(std::string texture, bool smooth, bool repeatable) :_texturepath(texture), _smooth(smooth), _repeatable(repeatable) {}
		TextureSettings() = default;
	public:
		// Inherited via SettingsBase
		virtual std::string ToStdString()const override;
	public:
		std::string _texturepath;
		bool _smooth = false;
		bool _repeatable = false;
	};
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(TextureSettings, _texturepath, _smooth, _repeatable)
}