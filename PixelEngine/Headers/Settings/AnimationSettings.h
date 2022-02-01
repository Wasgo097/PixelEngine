#pragma once
//base
#include"SettingsBase.h"
#include "Utility/ISerializable.h"

#include <map>
#include <SFML/System.hpp>
namespace Core{
	namespace Animation{
		enum class Direction;
	}
}
using nlohmann::json;
//#include <Objects/Extensions/Animation.h>
namespace Settings{
	class AnimationSettings :public SettingsBase,Utility::IJsonSerializable{
	public:
		//framescount key is a rows(y), value is a  columns (x), all columns and rows which will be used in animation; switchtime - switch between aniamtion 
		//rectsize - size of one frame on texture image
		AnimationSettings(sf::Vector2u rectsize, float switchtime, std::map<int, int> framescount, std::map<Core::Animation::Direction, int> directiontorow);
		AnimationSettings() = default;
	public:
		virtual std::string ToStdString()const override;
		virtual json JSerialize()const override;
		virtual bool JDeserialize(json json)override;
	public:
		const sf::Vector2u & GetRectSize()const;
		const float& GetSwitchTime()const;
		std::map<int, int> & GetFramesCount();
		std::map<Core::Animation::Direction, int> & GetDirectionRow();
	protected:
		sf::Vector2u _rectsize = sf::Vector2u(0, 0);
		float _switchtime = .0f;
		std::map<int, int> _framescount;
		std::map<Core::Animation::Direction, int> _directiontorow;
	};
}