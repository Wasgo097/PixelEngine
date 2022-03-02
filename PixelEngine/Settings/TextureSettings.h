#pragma once
#include"SettingsBase.h"
namespace Settings{
	class TextureSettings:public SettingsBase{
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
		bool operator ==(const TextureSettings& obj)const {
			return (_texturepath == obj._texturepath) &&
				(_smooth == obj._smooth) &&
				(_repeatable == obj._repeatable);
		}
	};
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(TextureSettings, _texturepath, _smooth, _repeatable)
}