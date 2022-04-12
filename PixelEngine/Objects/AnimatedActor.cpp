#include "Utility/CommonHeaders.h"
#include "AnimatedActor.h"
namespace Core {
	AnimatedActor::AnimatedActor(WorldBase* world, const Settings::ActorSettings& actorsettings, const Settings::TextureSettings& texturesettings, const Settings::AnimationSettings& animationsettings) :
		Actor(world, actorsettings, texturesettings),
		_animationsettings(animationsettings),
		_directiontorowref(_animationsettings._directiontorow)
	{
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
	void AnimatedActor::Tick(float deltatime) {
		Actor::Tick(deltatime);
		if (!_directiontorowref.empty()) {
			if (_animation)
				_animation->Tick(_animatedrow, deltatime);
			if (_animatedrow <= 4)
				_animatedrow = _directiontorowref.at(static_cast<AnimationEnums::Direction>(_animatedrow + 4));
		}
	}
	void AnimatedActor::Move(const sf::Vector2f& velocity) {
		Actor::Move(velocity);
		if (!_directiontorowref.empty()) {
			if (_velocity != sf::Vector2f(.0f, .0f)) {
				if (_velocity.x != 0) {
					if (_velocity.x > 0) {
						if (_directiontorowref.count(AnimationEnums::Direction::Right))
							_animatedrow = _directiontorowref[AnimationEnums::Direction::Right];
						else {
							_animatedrow = _directiontorowref.begin()->second;
							throw std::out_of_range("Wrong animation row in " + ToString() + " missed row (int int): " + std::to_string(static_cast<int>(AnimationEnums::Direction::Right)));
						}
					}
					else {
						if (_directiontorowref.count(AnimationEnums::Direction::Left))
							_animatedrow = _directiontorowref[AnimationEnums::Direction::Left];
						else {
							_animatedrow = _directiontorowref.begin()->second;
							throw std::out_of_range("Wrong animation row in " + ToString() + " missed row (int int): " + std::to_string(static_cast<int>(AnimationEnums::Direction::Left)));
						}
					}
				}
				else {
					if (_velocity.y > 0) {
						if (_directiontorowref.count(AnimationEnums::Direction::Down))
							_animatedrow = _directiontorowref[AnimationEnums::Direction::Down];
						else {
							_animatedrow = _directiontorowref.begin()->second;
							throw std::out_of_range("Wrong animation row in " + ToString() + " missed row (int int): " + std::to_string(static_cast<int>(AnimationEnums::Direction::Down)));
						}
					}
					else {
						if (_directiontorowref.count(AnimationEnums::Direction::Up))
							_animatedrow = _directiontorowref[AnimationEnums::Direction::Up];
						else {
							_animatedrow = _directiontorowref.begin()->second;
							throw std::out_of_range("Wrong animation row in " + ToString() + " missed row (int int): " + std::to_string(static_cast<int>(AnimationEnums::Direction::Up)));
						}
					}
				}
			}
			else {
				_animatedrow = _directiontorowref[AnimationEnums::Direction::DownIdle];
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
