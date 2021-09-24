#include "Objects/Actor.h"
#include "Core/World.h"
namespace Core{
	Actor::Actor(World * world, std::optional<std::string> texture_path, const Settings::ActorSettings & settings, sf::Vector2f velocity) :
		_world(world), _texturepath(texture_path), _settings(settings), _velocity(velocity){}
	bool & Actor::TickFlag(){
		return _tickon;
	}
	void Actor::Draw(sf::RenderWindow & window){
		if(_sprite)
			window.draw(*_sprite);
	}
	void Actor::Tick(float deltatime){
		if(_settings.GetActorType() == Settings::ActorType::Dynamic)
			_sprite->move(_velocity*deltatime);
	}
}