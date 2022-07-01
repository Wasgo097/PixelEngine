#pragma once
#include "Controller/ControllerBase.h"
namespace Controller {
	class EmptyController:public ControllerBase{
	public:
		EmptyController(Core::WorldBase* world);
		virtual ~EmptyController() = default;
	public:
		// Inherited via ControllerBase
		virtual void InitMainCharacterInputBindings() override;
		virtual void InitMainCharacter() override;
	};
}
