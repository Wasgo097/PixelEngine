#pragma once
#include "PXCore/Controller/ControllerBase.h"
#include "PXCore/World/WorldBase.h"
namespace Test {
	class ControllerForAnimationTest:public Core::Controller::ControllerBase{
	public:
		ControllerForAnimationTest(Core::World::WorldBase* world);
	public:
		// Inherited via ControllerBase
		virtual void InitMainCharacterInputBindings() override;
		virtual void InitMainCharacter() override;
	};
}