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
		try{
			json output;
			if(_texturepath)
				output["_texturepath"] = *_texturepath;
			else
				output["_texturepath"] = nullptr;
			output["_smooth"] = _smooth;
			output["_repeatable"] = _repeatable;
			return output;
		}
		catch(...){
			return json();
		}
	}

	bool TextureSettings::JDeserialize(json json){
		try{
			if(json["_mastervolume"]!=nullptr)
				_texturepath = json["_texturepath"];
			_smooth = json["_smooth"];
			_repeatable = json["_repeatable"];
			return true;
		}
		catch(...){
			return false;
		}
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