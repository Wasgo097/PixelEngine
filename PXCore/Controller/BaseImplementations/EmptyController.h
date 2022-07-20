#pragma once
#include "Controller/ControllerBase.h"
#include "World/WorldBase.h"
namespace Core::Controller {
	class EmptyController:public ControllerBase{
	public:
		EmptyController(Core::World::WorldBase* world_parent);
		virtual ~EmptyController() = default;

		// Inherited via ControllerBase
		virtual void InitMainCharacterInputBindings() override;
		virtual void InitMainCharacter() override;
	};
}
