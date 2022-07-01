#pragma once
#include "Enums/AnimationEnums.h"
#include "Settings/TextureSettings.h"
#include "Settings/AnimationSettings.h"
namespace Core{
	namespace Animation{
		class Animation{
		public:
			Animation(sf::Sprite & animated_sprite, const Settings::AnimationSettings & animation_settings);
		public:
			void Tick(int row, float deltatime);
		protected:
			std::map<int, int>& _count_of_columns_in_row;
			sf::Sprite & _animated_sprite;
			Settings::AnimationSettings _animation_settings;
			sf::IntRect _frame_on_texture;
			sf::Vector2u _movable_view_on_texture;
			float _elapsed_time = .0f;
			int _row = -1;
		};
	}
}