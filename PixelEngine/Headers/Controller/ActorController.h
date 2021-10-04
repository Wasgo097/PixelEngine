#pragma once
#include "ControllerStructs.h"
#include "Objects/ControlledActor.h"
#include "Settings/ControllerSettings.h"
#include <map>
#include <functional>
#include <memory>
namespace Controller{
	class ActorController{
	public:
		//ActorController(Settings::ControllerSettings settings):_settings(settings){}
	public:
		static bool TestEvent(const Key& k, sf::Event e);
		void DoAction(const Key& key);
		bool ServiceInput(sf::Event e);
	protected:
		//Settings::ControllerSettings _settings;
		//std::unique_ptr<Core::ControlledActor> _actor;
	};
}
