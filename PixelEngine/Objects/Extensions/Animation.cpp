#include "Utility/CommonHeaders.h"
#include "Animation.h"
namespace Core{
	namespace Animation{
		Animation::Animation(sf::Sprite & animatedsprite, const Settings::AnimationSettings & animationsettings) :
			_Sprite(animatedsprite), 
			_AnimationSettings(animationsettings),_CountOfColumnsFromRowRef(_AnimationSettings._framescount) {
			_FrameOnTexture.width = _AnimationSettings._rectsize.x;
			_FrameOnTexture.height = _AnimationSettings._rectsize.y;
		}
		void Animation::Tick(int row, float deltatime){
			if (_CurrentRow != row) {
				_CurrentRow = row;
				_MovableViewOnTexture.x = 0;
			}
			_MovableViewOnTexture.y = row;
			_totaltime += deltatime;
			if(_totaltime >= _AnimationSettings._switchtime){
				_totaltime -= _AnimationSettings._switchtime;
				_MovableViewOnTexture.x++;
				if(_MovableViewOnTexture.x >= _CountOfColumnsFromRowRef.at(_MovableViewOnTexture.y))
					_MovableViewOnTexture.x = 0;
			}
			_FrameOnTexture.left = _MovableViewOnTexture.x*_AnimationSettings._rectsize.x;
			_FrameOnTexture.top = _MovableViewOnTexture.y*_AnimationSettings._rectsize.y;
			_Sprite.setTextureRect(_FrameOnTexture);
		}
	}
}
