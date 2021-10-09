#pragma once
#include"SettingsBase.h"
#include <map>
namespace Core{
	namespace Animation{
		enum class Direction;
	}
}
//#include <Objects/Extensions/Animation.h>
namespace Settings{
	class AnimationSettings :public SettingsBase{
	public:
		//framescount key is a rows(y), value is a  columns (x), all columns and rows which will be used in animation; switchtime - switch between aniamtion 
		//rectsize - size of one frame on texture image
		AnimationSettings(sf::Vector2u rectsize, float switchtime, std::map<int, int> framescount, std::map<Core::Animation::Direction, int> directiontorow) :
			_rectsize(rectsize), _switchtime(switchtime), _framescount(framescount),_directiontorow(directiontorow){}
		AnimationSettings() = default;
		// Inherited via SettingsBase
		virtual std::string ToStdString()const override{
			std::stringstream stream;
			stream << "RectSize: " << _rectsize.x << " " << _rectsize.y << " Switch Time: " << _switchtime;
			for(const auto&[key, value] : _framescount)
				stream << " Rows: " << key << " Columns: " << value;
			return stream.str();
		}
		const sf::Vector2u & GetRectSize()const{
			return _rectsize;
		}
		const float& GetSwitchTime()const{
			return _switchtime;
		}
		std::map<int, int> & GetFramesCount(){
			return _framescount;
		}
		std::map<Core::Animation::Direction, int> & GetDirectionRow(){
			return _directiontorow;
		}
	protected:
		sf::Vector2u _rectsize = sf::Vector2u(0, 0);
		float _switchtime = .0f;
		std::map<int, int> _framescount;
		std::map<Core::Animation::Direction, int> _directiontorow;
	};
}