#include "CommonHeaders.h"
#include "Objects/Extensions/Animation.h"
namespace Core{
	namespace Animation{
		Animation::Animation(sf::Sprite & animatedsprite, const Settings::AnimationSettings & animationsettings) :_animatedsprite(animatedsprite), _settings(animationsettings){
			_frame.width = _settings._rectsize.x;
			_frame.height = _settings._rectsize.y;
		}
		void Animation::Tick(int row, float deltatime){
			_currentimage.y = row;
			_totaltime += deltatime;
			if(_totaltime >= _settings._switchtime){
				_totaltime -= _settings._switchtime;
				_currentimage.x++;
				if(_currentimage.x >= _settings._framescount.at(_currentimage.y))
					_currentimage.x = 0;
			}
			_frame.left = _currentimage.x*_settings._rectsize.x;
			_frame.top = _currentimage.y*_settings._rectsize.y;
			_animatedsprite.setTextureRect(_frame);
		}
	}
}
