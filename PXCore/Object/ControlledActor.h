#pragma once
#include "AnimatedActor.h"
#include "PXCore/Controller/ControllerBase.h"
namespace Core::Controller {
	class ControllerBase;
}
namespace Core::Object {
	class ControlledActor:public AnimatedActor{
	public:
		ControlledActor(World::WorldBase* world, const Settings::ActorSettings& actor_settings, const Settings::TextureSettings& texture_settings, const Settings::AnimationSettings& animation_settings,Controller::ControllerBase * controller);
		ControlledActor(const ControlledActor&) = delete;
		ControlledActor(ControlledActor&&) = delete;
		ControlledActor& operator=(const ControlledActor&) = delete;
		ControlledActor& operator=(ControlledActor&&) = delete;
		virtual ~ControlledActor() = default;

		virtual std::string ToString()const override;
	protected:
		Controller::ControllerBase* _controller = nullptr;
	};
}