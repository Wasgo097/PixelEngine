#pragma once
#include "Controller/ControllerBase.h"
namespace Controller {
	class EmptyController:public ControllerBase{
		// Inherited via ControllerBase
		virtual void SetMainCharacterInputBindings() override;
		virtual void SetMainCharacter() override;
	};
}
