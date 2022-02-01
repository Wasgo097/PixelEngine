#include "Settings/AnimationSettings.h"
#include <sstream>
//framescount key is a rows(y), value is a  columns (x), all columns and rows which will be used in animation; switchtime - switch between aniamtion 
//rectsize - size of one frame on texture image
namespace Settings{
	Settings::AnimationSettings::AnimationSettings(sf::Vector2u rectsize, float switchtime, std::map<int, int> framescount, std::map<Core::Animation::Direction, int> directiontorow) :
		_rectsize(rectsize), _switchtime(switchtime), _framescount(framescount), _directiontorow(directiontorow){}
	std::string AnimationSettings::ToStdString() const{
		std::stringstream stream;
		stream << "RectSize: " << _rectsize.x << " " << _rectsize.y << " Switch Time: " << _switchtime;
		for(const auto&[key, value] : _framescount)
			stream << " Rows: " << key << " Columns: " << value;
		return stream.str();
	}
	json AnimationSettings::JSerialize() const{
		try{
			json output;
			output["_rectsizex"] = _rectsize.x;
			output["_rectsizey"] = _rectsize.y;
			output["_switchtime"] = _switchtime;
			output.push_back(_framescount);
			output.push_back(_directiontorow);
			return output;
		}
		catch(...){
			return json();
		}
		return json();
	}
	bool AnimationSettings::JDeserialize(json json){
		try{
			_rectsize.x = json["_rectsizex"];
			_rectsize.y = json["_rectsizey"];
			_switchtime = json["_switchtime"];

			return true;
		}
		catch(...){
			return false;
		}
		return false;
	}
	const sf::Vector2u & AnimationSettings::GetRectSize() const{
		return _rectsize;
	}
	const float & AnimationSettings::GetSwitchTime() const{
		return _switchtime;
	}
	std::map<int, int>& AnimationSettings::GetFramesCount(){
		return _framescount;
	}
	std::map<Core::Animation::Direction, int>& AnimationSettings::GetDirectionRow(){
		return _directiontorow;
	}
}