#pragma once
#include"SettingsBase.h"
#include <map>
#include "Enums/AnimationEnums.h"
#include "Utility/BasicSFMLTypesToJson.h"
namespace Settings{
	class AnimationSettings :public SettingsBase{
	public:
		//framescount key is a rows(y), value is a  columns (x), all columns and rows which will be used in animation; switchtime - switch between aniamtion 
		//rectsize - size of one frame on texture image
		AnimationSettings(sf::Vector2u rectsize, float switchtime, std::map<int, int> framescount, std::map<AnimationEnums::Direction, int> directiontorow):_rectsize(rectsize),_switchtime(switchtime),
			_framescount(framescount),_directiontorow(directiontorow){}
		AnimationSettings() = default;
	public:
		virtual std::string ToStdString()const override;
	public:
		sf::Vector2u _rectsize;
		float _switchtime = .0f;
		//k - row number  v - count of columns
		std::map<int, int> _framescount;
		//k - direction v-row number
		std::map<AnimationEnums::Direction, int> _directiontorow;
		bool operator ==(const AnimationSettings& obj)const {
			return (_rectsize == obj._rectsize) &&
				(_switchtime == obj._switchtime) &&
				(_framescount == obj._framescount) &&
				(_directiontorow == obj._directiontorow);
		}
	};
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(AnimationSettings, _rectsize, _switchtime, _framescount, _directiontorow)
}