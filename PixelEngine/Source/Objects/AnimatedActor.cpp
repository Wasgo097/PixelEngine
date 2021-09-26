#include "Objects/AnimatedActor.h"
namespace Core{
	void AnimatedActor::Move(const sf::Vector2f & velocity){
		Actor::Move(velocity);
	}
	void AnimatedActor::Draw(sf::RenderWindow & window){
		Actor::Draw(window);
	}
}
