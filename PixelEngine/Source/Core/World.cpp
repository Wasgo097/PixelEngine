#include "Core/World.h"
#include "Core/ActorManager.h"
namespace Core{
	struct World::Impl{
		std::unique_ptr<ActorManager> _actormanager;
	};
}