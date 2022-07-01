#include "AnimatedActor.h"
namespace Core::Object {
	AnimatedActor::AnimatedActor(World::WorldBase* world, const Settings::ActorSettings& actor_settings, const Settings::TextureSettings& texture_settings, const Settings::AnimationSettings& animation_settings) :
		Actor(world, actor_settings, texture_settings),
		_animation_settings(animation_settings),
		_animation(std::make_unique<Extension::Animation>(*_sprite, _animation_settings)),
		_direction_row(_animation_settings.direction_to_row)
	{
		if (!_direction_row.empty()) {
			_animated_row = _direction_row.at(AnimationEnums::Direction::DownIdle);
			if (_sprite) {
				sf::Vector2f temp_origin(_animation_settings.rect_size.x, _animation_settings.rect_size.y);
				temp_origin.x /= 2.0f;
				_sprite->setOrigin(temp_origin);
				_sprite->setPosition(_actor_settings.position);
				if (_direction_row.size() < 1) {
					throw std::invalid_argument("animationrows has too less size");
				}
			}
		}
	}
	void AnimatedActor::Tick(float delta_time) {
		Actor::Tick(delta_time);
		if (_direction_row.empty()) return;
		if (_animation)
			_animation->Tick(_animated_row, delta_time);
		if (_velocity == sf::Vector2f())
			_animated_row = _direction_row.at(AnimationEnums::Direction::DownIdle);
	}
	void AnimatedActor::Move(const sf::Vector2f& velocity) {
		Actor::Move(velocity);
		if (_direction_row.empty()) return;
		if (_velocity.x != 0) {
			if (_velocity.x > 0) {
				if (_direction_row.count(AnimationEnums::Direction::Right))
					_animated_row = _direction_row.at(AnimationEnums::Direction::Right);
				else {
					_animated_row = _direction_row.begin()->second;
					throw std::out_of_range("Wrong animation row in " + ToString() + " missed row (int int): " + std::to_string(static_cast<int>(AnimationEnums::Direction::Right)));
				}
			}
			else {
				if (_direction_row.count(AnimationEnums::Direction::Left))
					_animated_row = _direction_row.at(AnimationEnums::Direction::Left);
				else {
					_animated_row = _direction_row.begin()->second;
					throw std::out_of_range("Wrong animation row in " + ToString() + " missed row (int int): " + std::to_string(static_cast<int>(AnimationEnums::Direction::Left)));
				}
			}
		}
		else if (_velocity.y != 0) {
			if (_velocity.y > 0) {
				if (_direction_row.count(AnimationEnums::Direction::Down))
					_animated_row = _direction_row.at(AnimationEnums::Direction::Down);
				else {
					_animated_row = _direction_row.begin()->second;
					throw std::out_of_range("Wrong animation row in " + ToString() + " missed row (int int): " + std::to_string(static_cast<int>(AnimationEnums::Direction::Down)));
				}
			}
			else {
				if (_direction_row.count(AnimationEnums::Direction::Up))
					_animated_row = _direction_row.at(AnimationEnums::Direction::Up);
				else {
					_animated_row = _direction_row.begin()->second;
					throw std::out_of_range("Wrong animation row in " + ToString() + " missed row (int int): " + std::to_string(static_cast<int>(AnimationEnums::Direction::Up)));
				}
			}
		}
	}

	std::string AnimatedActor::ToString() const { return "Default AnimatedActor ToString"; }
}
