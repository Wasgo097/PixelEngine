#include "Core/World.h"
#include "Core/ActorManager.h"
namespace Core{
	World::World(Settings::WorldSettings && worlsettings, Settings::WindowSettings && windowsettings) :
		_worldsettings(std::move(worlsettings)), _windowsettings(std::move(windowsettings)),
		_actormanager(std::make_unique<ActorManager>(_worldsettings.BufferSize(), _worldsettings.GcFrequentLevel(),_worldsettings.CycleToMove())){}
	World::~World(){
		_actormanager->Terminate();
		_actormanager->Wait();
	}
}