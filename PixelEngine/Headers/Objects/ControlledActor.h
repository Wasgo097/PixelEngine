#pragma once
#include "AnimatedActor.h"
#include "Settings/ControlSettings.h"
#include "Controller/ActorController.h"
namespace Core{
	class ControlledActor:public AnimatedActor{
		ControlledActor(World* world, const Settings::ActorSettings & settings, const Settings::AnimationSettings& animationsettings,
			const Settings::ControlSettings& controlsettings);
		ControlledActor(const ControlledActor&) = delete;
		ControlledActor(ControlledActor&&) = delete;
		ControlledActor& operator=(const ControlledActor&) = delete;
		ControlledActor& operator=(ControlledActor&&) = delete;
		virtual ~ControlledActor() = default;
	protected:
		Settings::ControlSettings _controlsettings;
		std::unique_ptr<Controller::ActorController> _controller;
	};
}