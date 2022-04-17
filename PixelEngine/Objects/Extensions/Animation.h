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
			std::map<int, int>& _CountOfColumnsFromRowRef;
			sf::Sprite & _Sprite;
			Settings::AnimationSettings _AnimationSettings;
			sf::IntRect _FrameOnTexture;
			sf::Vector2u _MovableViewOnTexture;
			float _totaltime = .0f;
			int _CurrentRow = -1;
		};
	}
}