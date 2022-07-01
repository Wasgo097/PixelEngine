#pragma once
#include "Controller/ControllerBase.h"
#include "World/WorldBase.h"
namespace Core::Controller {
	class EmptyController:public ControllerBase{
	public:
		EmptyController(Core::World::WorldBase* world);
		virtual ~EmptyController() = default;

		// Inherited via ControllerBase
		virtual void InitMainCharacterInputBindings() override;
		virtual void InitMainCharacter() override;
	protected:
		Core::World::WorldBase* _world;
	};
}
