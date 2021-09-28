#pragma once
#include"SettingsBase.h"
namespace Settings{
	class AnimationSettings :public SettingsBase{
	public:
		//framescount k-rows y, v- columns x,	all columns and rows which will be used in animation; switchtime - switch between aniamtion 
		//rectsize - size of one frame on texture image
		AnimationSettings(sf::Vector2u rectsize, std::map<int, int> framescount, float switchtime) :_rectsize(rectsize), _switchtime(switchtime), _framescount(framescount){}
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
		const std::map<int, int> & GetFramesCount()const{
			return _framescount;
		}
		const float& GetSwitchTime()const{
			return _switchtime;
		}
	protected:
		sf::Vector2u _rectsize = sf::Vector2u(0, 0);
		float _switchtime = .0f;
		std::map<int, int> _framescount;
	};
}