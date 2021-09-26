#pragma once
#include "CommonHeaders.h"
#include "Settings/TextureSettings.h"
namespace Core{
	namespace Animation{
		class Animation{
		public:
			Animation(sf::Sprite & animatedsprite, const Settings::AnimationTextureSettings & animationsettings):_animatedsprite(animatedsprite),_settings(animationsettings){
				_frame.width = _settings.GetRectSize().x;
				_frame.height = _settings.GetRectSize().y;
			}
			Animation() = default;
			void Tick(int row,float deltatime){
				_currentimage.y = row;
				_totaltime += deltatime;
				if(_totaltime >= _settings.GetSwitchTime()){
					_totaltime -= _settings.GetSwitchTime();
					_currentimage.x++;
					if(_currentimage.x >= _settings.GetColumns())
						_currentimage.x = 0;
				}
				_frame.left = _currentimage.x*_settings.GetRectSize().x;
				_frame.top = _currentimage.y*_settings.GetRectSize().y;
				_animatedsprite.setTextureRect(_frame);
			}
		protected:
			sf::Sprite & _animatedsprite;
			Settings::AnimationTextureSettings _settings;
			sf::IntRect _frame;
			sf::Vector2u _currentimage;
			float _totaltime = .0f;
		};
	}
}