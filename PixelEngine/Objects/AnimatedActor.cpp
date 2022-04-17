#include "Utility/CommonHeaders.h"
#include "AnimatedActor.h"
namespace Core {
	AnimatedActor::AnimatedActor(WorldBase* world, const Settings::ActorSettings& actorsettings, const Settings::TextureSettings& texturesettings, const Settings::AnimationSettings& animationsettings) :
		Actor(world, actorsettings, texturesettings),
		_animationsettings(animationsettings),
		_animation(std::make_unique<Animation::Animation>(*_sprite, _animationsettings)),
		_directiontorowref(_animationsettings._directiontorow)
	{
		if (!_directiontorowref.empty()) {
			_animatedrow = _directiontorowref.at(AnimationEnums::Direction::DownIdle);
			if (_sprite) {
				sf::Vector2f temporigin(_animationsettings._rectsize.x, _animationsettings._rectsize.y);
				temporigin.x /= 2.0f;
				_sprite->setOrigin(temporigin);
				_sprite->setPosition(_actorsettings._position);
				if (_directiontorowref.size() < 1) {
					throw std::invalid_argument("animationrows has too less size");
				}
			}
		}
	}
	void AnimatedActor::Tick(float deltatime) {
		if (!_directiontorowref.empty()) {
			if (_animation)
				_animation->Tick(_animatedrow, deltatime);
			if (_velocity == sf::Vector2f())
				_animatedrow = _directiontorowref.at(AnimationEnums::Direction::DownIdle);
		}
		Actor::Tick(deltatime);
	}
	void AnimatedActor::Move(const sf::Vector2f& velocity) {
		Actor::Move(velocity);
		if (!_directiontorowref.empty()) {
			if (_velocity.x != 0) {
				if (_velocity.x > 0) {
					if (_directiontorowref.count(AnimationEnums::Direction::Right))
						_animatedrow = _directiontorowref.at(AnimationEnums::Direction::Right);
					else {
						_animatedrow = _directiontorowref.begin()->second;
						throw std::out_of_range("Wrong animation row in " + ToString() + " missed row (int int): " + std::to_string(static_cast<int>(AnimationEnums::Direction::Right)));
					}
				}
				else {
					if (_directiontorowref.count(AnimationEnums::Direction::Left))
						_animatedrow = _directiontorowref.at(AnimationEnums::Direction::Left);
					else {
						_animatedrow = _directiontorowref.begin()->second;
						throw std::out_of_range("Wrong animation row in " + ToString() + " missed row (int int): " + std::to_string(static_cast<int>(AnimationEnums::Direction::Left)));
					}
				}
			}
			else if(_velocity.y!=0) {
				if (_velocity.y > 0) {
					if (_directiontorowref.count(AnimationEnums::Direction::Down))
						_animatedrow = _directiontorowref.at(AnimationEnums::Direction::Down);
					else {
						_animatedrow = _directiontorowref.begin()->second;
						throw std::out_of_range("Wrong animation row in " + ToString() + " missed row (int int): " + std::to_string(static_cast<int>(AnimationEnums::Direction::Down)));
					}
				}
				else {
					if (_directiontorowref.count(AnimationEnums::Direction::Up))
						_animatedrow = _directiontorowref.at(AnimationEnums::Direction::Up);
					else {
						_animatedrow = _directiontorowref.begin()->second;
						throw std::out_of_range("Wrong animation row in " + ToString() + " missed row (int int): " + std::to_string(static_cast<int>(AnimationEnums::Direction::Up)));
					}
				}
			}
		}
	}
	void AnimatedActor::ConstPush(const sf::Vector2f& constvelocity) {
		Actor::ConstPush(constvelocity);
	}
	void AnimatedActor::Draw(sf::RenderWindow& window) {
		Actor::Draw(window);
	}
	std::string AnimatedActor::ToString() const { return "Default AnimatedActor ToString"; }
}
