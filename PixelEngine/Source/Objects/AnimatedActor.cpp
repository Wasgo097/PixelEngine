#include "CommonHeaders.h"
#include "Objects/AnimatedActor.h"
namespace Core{
	AnimatedActor::AnimatedActor(World* world, const Settings::ActorSettings & settings, const Settings::AnimationSettings& animatedtexture, std::map<Animation::AnimationRow, int> animationrows) :
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
			_animatedrow = _animationrows[static_cast<Animation::AnimationRow>(_animatedrow + 4)];
	}
	void AnimatedActor::Move(const sf::Vector2f & velocity){
		Actor::Move(velocity);
		if(_velocity != sf::Vector2f(.0f, .0f)){
			if(_velocity.x != 0){
				if(_velocity.x > 0){
					if(_animationrows.count(Animation::AnimationRow::Right))
						_animatedrow = _animationrows[Animation::AnimationRow::Right];
					else{
						_animatedrow = _animationrows.begin()->second;
						throw std::out_of_range("Wrong animation row in " + ToString() + " missed row (int int): " + std::to_string(static_cast<int>(Animation::AnimationRow::Right)));
					}
				}
				else{
					if(_animationrows.count(Animation::AnimationRow::Left))
						_animatedrow = _animationrows[Animation::AnimationRow::Left];
					else{
						_animatedrow = _animationrows.begin()->second;
						throw std::out_of_range("Wrong animation row in " + ToString() + " missed row (int int): " + std::to_string(static_cast<int>(Animation::AnimationRow::Left)));
					}
				}
			}
			else{
				if(_velocity.y > 0){
					if(_animationrows.count(Animation::AnimationRow::Down))
						_animatedrow = _animationrows[Animation::AnimationRow::Down];
					else{
						_animatedrow = _animationrows.begin()->second;
						throw std::out_of_range("Wrong animation row in " + ToString() + " missed row (int int): " + std::to_string(static_cast<int>(Animation::AnimationRow::Down)));
					}
				}
				else{
					if(_animationrows.count(Animation::AnimationRow::Up))
						_animatedrow = _animationrows[Animation::AnimationRow::Up];
					else{
						_animatedrow = _animationrows.begin()->second;
						throw std::out_of_range("Wrong animation row in " + ToString() + " missed row (int int): " + std::to_string(static_cast<int>(Animation::AnimationRow::Up)));
					}
				}
			}
		}
		else{
			_animatedrow = _animationrows[Animation::AnimationRow::DownIdle];
		}
	}
	void AnimatedActor::Push(const sf::Vector2f & constvelocity){
		Actor::Push(constvelocity);
	}
	void AnimatedActor::Draw(sf::RenderWindow & window){
		Actor::Draw(window);
	}
}
