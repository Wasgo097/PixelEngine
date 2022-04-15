#pragma once
#include "Controller/ControllerBase.h"
namespace Test {
	class ControllerForAnimationTest:public Controller::ControllerBase{
	public:
		ControllerForAnimationTest(Core::WorldBase* world);
	public:
		// Inherited via ControllerBase
		virtual void InitMainCharacterInputBindings() override;
		virtual void InitMainCharacter() override;
	};
}