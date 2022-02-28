#include "CommonHeaders.h"
#include "Core/World.h"
#include "Core/ActorManager.h"
namespace Core {
	World::World(const Settings::WorldSettings& worlsettings) :
		_worldsettings(worlsettings)
		,_actormanager(std::make_unique<ActorManager>(worlsettings._buffersize, worlsettings._gcfrequentlevel, worlsettings._cycletomove))
	{}
	World::~World() {
		if (_actormanager) {
			_actormanager->Terminate();
			_actormanager->Wait();
		}
		//std::cout << "World destructor\n";
	}
	void World::Draw(sf::RenderWindow& window) {
		//todo: draw whole world
		if (_actormanager)
			_actormanager->Draw(window);
	}
	void World::Update(float delta){
		if (_actormanager)
			_actormanager->Update(delta);
	}
	void World::TermianateActorManager()
	{
		if (_actormanager)
			_actormanager->Terminate();
	}
	void World::WaitOnActorManager()
	{
		if (_actormanager)
			_actormanager->Wait();
	}
}