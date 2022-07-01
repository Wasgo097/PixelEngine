#include "Utility/CommonHeaders.h"
#include "Animation.h"
namespace Core {
	namespace Animation {
		Animation::Animation(sf::Sprite& animated_sprite, const Settings::AnimationSettings& animation_settings) :
			_animated_sprite{ animated_sprite },
			_animation_settings{ animation_settings }, _count_of_columns_in_row{ _animation_settings.frames_count } {
			_frame_on_texture.width = _animation_settings.rect_size.x;
			_frame_on_texture.height = _animation_settings.rect_size.y;
		}
		void Animation::Tick(int row, float deltatime) {
			if (_row != row) {
				_row = row;
				_movable_view_on_texture.x = 0;
			}
			_movable_view_on_texture.y = row;
			_elapsed_time += deltatime;
			if (_elapsed_time >= _animation_settings.switch_time) {
				_elapsed_time -= _animation_settings.switch_time;
				_movable_view_on_texture.x++;
				if (_movable_view_on_texture.x >= _count_of_columns_in_row.at(_movable_view_on_texture.y))
					_movable_view_on_texture.x = 0;
			}
			_frame_on_texture.left = _movable_view_on_texture.x * _animation_settings.rect_size.x;
			_frame_on_texture.top = _movable_view_on_texture.y * _animation_settings.rect_size.y;
			_animated_sprite.setTextureRect(_frame_on_texture);
		}
	}
}