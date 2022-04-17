#pragma once
#include "Enums/AnimationEnums.h"
#include "Settings/TextureSettings.h"
#include "Settings/AnimationSettings.h"
namespace Core{
	namespace Animation{
		class Animation{
		public:
			Animation(sf::Sprite & animatedsprite, const Settings::AnimationSettings & animationsettings);
		public:
			void Tick(int row, float deltatime);
		protected:
			std::map<int, int>& _CountOfColumnsFromRow;
			sf::Sprite & _animatedsprite;
			Settings::AnimationSettings _settings;
			sf::IntRect _frame;
			sf::Vector2u _currentimage;
			float _totaltime = .0f;
			int _CurrentRow = -1;
		};
	}
}