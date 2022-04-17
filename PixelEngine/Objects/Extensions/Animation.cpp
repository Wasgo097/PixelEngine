#include "Utility/CommonHeaders.h"
#include "Animation.h"
namespace Core{
	namespace Animation{
		Animation::Animation(sf::Sprite & animatedsprite, const Settings::AnimationSettings & animationsettings) :
			_animatedsprite(animatedsprite), 
			_settings(animationsettings),_CountOfColumnsFromRow(_settings._framescount) {
			_frame.width = _settings._rectsize.x;
			_frame.height = _settings._rectsize.y;
		}
		void Animation::Tick(int row, float deltatime){
			if (_CurrentRow != row) {
				_CurrentRow = row;
				_currentimage.x = 0;
			}
			_currentimage.y = row;
			_totaltime += deltatime;
			if(_totaltime >= _settings._switchtime){
				_totaltime -= _settings._switchtime;
				_currentimage.x++;
				if(_currentimage.x >= _CountOfColumnsFromRow.at(_currentimage.y))
					_currentimage.x = 0;
			}
			_frame.left = _currentimage.x*_settings._rectsize.x;
			_frame.top = _currentimage.y*_settings._rectsize.y;
			_animatedsprite.setTextureRect(_frame);
		}
	}
}
