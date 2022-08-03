#pragma once
#include "PXCore/Controller/ControllerBase.h"
#include "PXCore/World/WorldBase.h"
namespace Test {
	class ControllerForForestTest :public Core::Controller::ControllerBase{
	public:
		ControllerForForestTest(Core::World::WorldBase* world, const Settings::WorldSettings& world_settings);
		// Inherited via ControllerBase
		virtual void InitMainCharacterInputBindings() override;
		virtual void InitMainCharacter() override;
	};
}