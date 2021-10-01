#include "CommonHeaders.h"
#include "Objects/AnimatedActor.h"
namespace Core{
	AnimatedActor::AnimatedActor(World* world, const Settings::ActorSettings & settings, const Settings::AnimationSettings& animatedtexture, std::map<Animation::Direction, int> animationrows) :
		Actor(world, settings),
		_animationsettings(animatedtexture),
		_animationrows(std::move(animationrows)){
		sf::Vector2f temporigin(_animationsettings.GetRectSize().x, _animationsettings.GetRectSize().y);
		temporigin.x /= 2.0f;
		_sprite->setOrigin(temporigin);
		_sprite->setPosition(_settings.GetPosition());
		if(_animationrows.size() < 1){
			throw std::invalid_argument("animationrows has too less size");
		}
	}
	void AnimatedActor::Tick(float deltatime){
		Actor::Tick(deltatime);
		_animation->Tick(_animatedrow, deltatime);
		if(_animatedrow<=4)
			_animatedrow = _animationrows[static_cast<Animation::Direction>(_animatedrow + 4)];
	}
	void AnimatedActor::Move(const sf::Vector2f & velocity){
		Actor::Move(velocity);
		if(_velocity != sf::Vector2f(.0f, .0f)){
			if(_velocity.x != 0){
				if(_velocity.x > 0){
					if(_animationrows.count(Animation::Direction::Right))
						_animatedrow = _animationrows[Animation::Direction::Right];
					else{
						_animatedrow = _animationrows.begin()->second;
						throw std::out_of_range("Wrong animation row in " + ToString() + " missed row (int int): " + std::to_string(static_cast<int>(Animation::Direction::Right)));
					}
				}
				else{
					if(_animationrows.count(Animation::Direction::Left))
						_animatedrow = _animationrows[Animation::Direction::Left];
					else{
						_animatedrow = _animationrows.begin()->second;
						throw std::out_of_range("Wrong animation row in " + ToString() + " missed row (int int): " + std::to_string(static_cast<int>(Animation::Direction::Left)));
					}
				}
			}
			else{
				if(_velocity.y > 0){
					if(_animationrows.count(Animation::Direction::Down))
						_animatedrow = _animationrows[Animation::Direction::Down];
					else{
						_animatedrow = _animationrows.begin()->second;
						throw std::out_of_range("Wrong animation row in " + ToString() + " missed row (int int): " + std::to_string(static_cast<int>(Animation::Direction::Down)));
					}
				}
				else{
					if(_animationrows.count(Animation::Direction::Up))
						_animatedrow = _animationrows[Animation::Direction::Up];
					else{
						_animatedrow = _animationrows.begin()->second;
						throw std::out_of_range("Wrong animation row in " + ToString() + " missed row (int int): " + std::to_string(static_cast<int>(Animation::Direction::Up)));
					}
				}
			}
		}
		else{
			_animatedrow = _animationrows[Animation::Direction::DownIdle];
		}
	}
	void AnimatedActor::Push(const sf::Vector2f & constvelocity){
		Actor::Push(constvelocity);
	}
	void AnimatedActor::Draw(sf::RenderWindow & window){
		Actor::Draw(window);
	}
}
