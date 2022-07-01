#pragma once
#include"SettingsBase.h"
#include <map>
#include "Enums/AnimationEnums.h"
#include "Utility/BasicSFMLTypesToJson.h"
namespace Settings {
	struct AnimationSettings :public SettingsBase {
		//framescount key is a rows(y), value is a  columns (x), all columns and rows which will be used in animation; switchtime - switch between aniamtion 
		//rectsize - size of one frame on texture image
		AnimationSettings(sf::Vector2u rect_size, float switch_time, std::map<int, int> frames_count, std::map<AnimationEnums::Direction, int> direction_to_row) :rect_size{ rect_size }, switch_time{ switch_time },
			frames_count{ frames_count }, direction_to_row{ direction_to_row } {}
		AnimationSettings() = default;
		virtual std::string ToStdString()const override;
		sf::Vector2u rect_size;
		float switch_time = .0f;
		//k - row number  v - count of columns
		std::map<int, int> frames_count;
		//k - direction v-row number
		std::map<AnimationEnums::Direction, int> direction_to_row;

		bool operator ==(const AnimationSettings& obj)const {
			return (rect_size == obj.rect_size) &&
				(switch_time == obj.switch_time) &&
				(frames_count == obj.frames_count) &&
				(direction_to_row == obj.direction_to_row);
		}
	};
}