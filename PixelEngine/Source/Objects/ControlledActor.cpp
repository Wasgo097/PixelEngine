#include "CommonHeaders.h"
#include "Objects/ControlledActor.h"
namespace Core{
	void ControlledActor::Tick(float deltatime){
		AnimatedActor::Tick(deltatime);
	}
	void ControlledActor::Move(const sf::Vector2f & velocity){
		AnimatedActor::Move(velocity);
	}
	void ControlledActor::Push(const sf::Vector2f & constvelocity){
		AnimatedActor::Push(constvelocity);
	}
	void ControlledActor::Draw(sf::RenderWindow & window){
		AnimatedActor::Draw(window);
	}
	std::string ControlledActor::ToString() const{ return "Default ControlledActor ToString"; }
}