#include "Objects/Actor.h"
namespace Core{
	bool & Actor::TickFlag(){
		return _tickon;
	}
	void Actor::Draw(sf::RenderWindow & window){
		if(_sprite)
			window.draw(*_sprite);
	}
	void Actor::Tick(float deltatime){
		_sprite->move(_velocity*deltatime);
	}
}