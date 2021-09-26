#pragma once
#include"SettingsBase.h"
namespace Settings{
	class TextureSettings:public SettingsBase{
	public:
		TextureSettings(std::optional<std::string> texture,bool Smooth,bool repeatable):_texturepath(texture),_smooth(Smooth), _repeatable(repeatable){}
		TextureSettings() = default;
		// Inherited via SettingsBase
		virtual std::string ToStdString() override{
			std::stringstream stream;
			std::string path = "";
			if(_texturepath)
				path = *_texturepath;
			stream << "Texture Path: " << path << " Smooth: " << _smooth << " Repeatable: " << _repeatable;
			return stream.str();
		}
		const std::optional<std::string>& TexturePath()const{
			return _texturepath;
		}
		const bool & Smooth()const{
			return _smooth;
		}
		const bool & Repeatable()const{
			return _repeatable;
		}
	protected:
		std::optional<std::string> _texturepath;
		bool _smooth = false;
		bool _repeatable = false;
	};
}