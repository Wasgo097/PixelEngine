#include "Animation.h"
#include <stdexcept>
namespace Core::Object::Components {
	Animation::Animation(Core::Object::Actor* parent, sf::Sprite& animated_sprite, const Settings::AnimationSettings& animation_settings) :
		ActorComponentBase(parent),
		_animated_sprite{ animated_sprite },
		_animation_settings{ animation_settings }, _count_of_columns_in_row{ _animation_settings.frames_count } {
		_frame_on_texture.width = _animation_settings.rect_size.x;
		_frame_on_texture.height = _animation_settings.rect_size.y;
	}
	void Animation::Tick(float delta_time) {
		if (!_initialized)
			throw std::runtime_error("Tick uninitialized ActorComponent");
		_movable_view_on_texture.y = _row;
		_elapsed_time += delta_time;
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
	void Animation::InitComponent() {
		SetTickFlag(true);
		_initialized = true;
	}
	void Animation::SetRow(int row) {
		if (_row != row) {
			_row = row;
			_movable_view_on_texture.x = 0;
			_elapsed_time = .0f;
		}
	}
	void Animation::SetRowAndSetTexture(int row) {
		SetRow(row);
		_movable_view_on_texture.y = _row;
		_movable_view_on_texture.x = 0;
		_frame_on_texture.left = _movable_view_on_texture.x * _animation_settings.rect_size.x;
		_frame_on_texture.top = _movable_view_on_texture.y * _animation_settings.rect_size.y;
		_animated_sprite.setTextureRect(_frame_on_texture);
	}
}
