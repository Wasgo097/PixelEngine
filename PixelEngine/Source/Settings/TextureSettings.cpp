#include "Settings/TextureSettings.h"
#include <sstream>

namespace Settings{
	TextureSettings::TextureSettings(std::optional<std::string> texture, bool smooth, bool repeatable) :_texturepath(texture), _smooth(smooth), _repeatable(repeatable){}
	std::string TextureSettings::ToStdString() const{
		std::stringstream stream;
		std::string path = "";
		if(_texturepath)
			path = *_texturepath;
		stream << "Texture Path: " << path << " Smooth: " << _smooth << " Repeatable: " << _repeatable;
		return stream.str();
	}
	json TextureSettings::JSerialize() const{
		return json();
	}

	bool TextureSettings::JDeserialize(json json){
		return false;
	}

	const std::optional<std::string>& TextureSettings::TexturePath() const{
		return _texturepath;
	}

	bool  TextureSettings::Smooth() const{
		return _smooth;
	}

	bool TextureSettings::Repeatable() const{
		return _repeatable;
	}
}