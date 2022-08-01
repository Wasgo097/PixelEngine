#pragma once
#include "PXCore/Object/Actor.h"
#include "PXUtilities/Interfaces/ITimeObserver.h"
namespace Core::World {
	class WorldBase;
}
namespace Test {
	class Tree :public Core::Object::Actor, public ITimeObserver {
	public:
		Tree(Core::World::WorldBase* world, const Settings::ActorSettings& actor_settings, const Settings::TextureSettings& texture_settings);
		// Inherited via ITimeObserver
		virtual void SecondPassed(unsigned int second) override;
		virtual void MinutePassed(unsigned int minute) override {};
	protected:
		int _growing_counter = 0;
	};
}