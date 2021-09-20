#include "Objects/Actor.h"
namespace Core{
	bool & Actor::TickFlag(){
		return _tickon;
	}
	void Actor::Draw(sf::RenderWindow & window){}
	void Actor::Tick(double time){}
}