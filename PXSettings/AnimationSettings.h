#pragma once
#include <map>
#include "PXUtilities/Enums/AnimationEnums.h"
#include <SFML/System/Vector2.hpp>
namespace Settings {
	struct AnimationSettings {
		//framescount key is a rows(y), value is a  columns (x), all columns and rows which will be used in animation; switchtime - switch between aniamtion 
		//rectsize - size of one frame on texture image
		AnimationSettings(sf::Vector2u rect_size, float switch_time, const std::map<int, int>& frames_count, const std::map<AnimationEnums::Direction, int>& direction_to_row) :rect_size{ rect_size }, switch_time{ switch_time },
			frames_count{ frames_count }, direction_to_row{ direction_to_row } {}
		AnimationSettings() = default;

		bool operator ==(const AnimationSettings& obj)const {
			return (rect_size == obj.rect_size) &&
				(switch_time == obj.switch_time) &&
				(frames_count == obj.frames_count) &&
				(direction_to_row == obj.direction_to_row);
		}

		sf::Vector2u rect_size;
		float switch_time = .0f;
		//k - row number  v - count of columns
		std::map<int, int> frames_count;
		//k - direction v-row number
		std::map<AnimationEnums::Direction, int> direction_to_row;
	};
}