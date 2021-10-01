#pragma once
#include "Settings/TextureSettings.h"
#include "Settings/AnimationSettings.h"
namespace Core{
	namespace Animation{
		enum class AnimationRow{
			None,
			Left,
			Up,
			Right,
			Down,
			LeftIdle,
			UpIdle,
			RightIdle,
			DownIdle
		};
		class Animation{
		public:
			Animation(sf::Sprite & animatedsprite, const Settings::AnimationSettings & animationsettings);
			Animation() = default;
			void Tick(int row, float deltatime);
		protected:
			sf::Sprite & _animatedsprite;
			Settings::AnimationSettings _settings;
			sf::IntRect _frame;
			sf::Vector2u _currentimage;
			float _totaltime = .0f;
		};
	}
}