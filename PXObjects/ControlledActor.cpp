#include "Utility/CommonHeaders.h"
#include "ControlledActor.h"
#include "Controller/ControllerBase.h"
namespace Core{
	ControlledActor::ControlledActor(WorldBase* world, const Settings::ActorSettings& actor_settings, const Settings::TextureSettings& texture_settings, const Settings::AnimationSettings& animation_settings, Controller::ControllerBase* controller)
		:AnimatedActor(world, actor_settings, texture_settings, animation_settings), _controller{ controller }{
	}

	std::string ControlledActor::ToString() const{ 
		return "Default ControlledActor ToString"; 
	}
}