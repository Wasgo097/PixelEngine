#include "CommonHeaders.h"
#include "Core/World.h"
#include "Core/ActorManager.h"
namespace Core{
	World::World(const Settings::WorldSettings & worlsettings) :
		_worldsettings(worlsettings),_actormanager(std::make_unique<ActorManager>(_worldsettings._buffersize, _worldsettings._gcfrequentlevel, _worldsettings._cycletomove)){}
	World::~World(){
		_actormanager->Terminate();
		_actormanager->Wait();
	}
	void World::Draw(sf::RenderWindow & window){
		//todo: draw whole world
		_actormanager->Draw(window);
	}
}