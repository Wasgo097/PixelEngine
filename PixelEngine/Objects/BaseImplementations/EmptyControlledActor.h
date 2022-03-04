#pragma once
#include "Objects/ControlledActor.h"
namespace Core {
	class EmptyControlledActor:public ControlledActor {
	public:
		EmptyControlledActor(WorldBase* world, const Settings::ActorSettings& actorsettings, const Settings::TextureSettings& texturesettings, const Settings::AnimationSettings& animationsettings, Controller::ControllerBase* controller);
		virtual ~EmptyControlledActor() = default;
	};
}
