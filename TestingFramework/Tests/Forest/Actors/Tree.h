#pragma once
#include "PXCore/Object/Actor.h"
namespace Core::World {
	class WorldBase;
}
namespace Test {
	class Tree:public Core::Object::Actor{
	public:
		Tree(Core::World::WorldBase* world, const Settings::ActorSettings& actor_settings, const Settings::TextureSettings& texture_settings);
	};
}