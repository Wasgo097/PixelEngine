#pragma once
#include "PXCore/World/WorldBase.h"
namespace Test {
	class WorldForAnimationTest:public Core::World::WorldBase{
	public:
		WorldForAnimationTest(const Settings::WorldSettings& worlsettings = Settings::WorldSettings(), Core::Engine* parrent = nullptr);
	public:
		virtual void CheckQuit()override;
		virtual void CreateWorldBaseComponents() override {}
	};
}
