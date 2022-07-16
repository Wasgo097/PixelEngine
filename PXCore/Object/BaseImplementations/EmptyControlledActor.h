#pragma once
#include "PXCore/Object/ControlledActor.h"
namespace Core::Object {
	class EmptyControlledActor:public ControlledActor {
	public:
		EmptyControlledActor(World::WorldBase* world, const Settings::ActorSettings& actorsettings, const Settings::TextureSettings& texturesettings, const Settings::AnimationSettings& animationsettings, Core::Controller::ControllerBase* controller);
	};
}
