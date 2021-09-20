#include "Core/World.h"
#include "Core/ActorManager.h"
namespace Core{
	World::World(const Settings::WorldSettings & worlsettings, const Settings::WindowSettings & windowsettings) :
		_worldsettings(worlsettings), _windowsettings(windowsettings),
		_actormanager(std::make_unique<ActorManager>(_worldsettings.BufferSize(), _worldsettings.GcFrequentLevel(),_worldsettings.CycleToMove())){}
	World::~World(){
		_actormanager->Terminate();
		_actormanager->Wait();
	}
}