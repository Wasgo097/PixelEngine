#pragma once
#include <SFML/Window/Event.hpp>
#include "ControllerStructs.h"
#include <memory>
#include <map>
#include <functional>
namespace Core {
	class ControlledActor;
}
namespace Controller {
	class ControllerBase {
	public:
		ControllerBase();
		virtual ~ControllerBase() = default;
		virtual void InitMainCharacterInputBindings() = 0;
		virtual void InitMainCharacter() = 0;
		virtual void ServiceInput(sf::Event current_event);
		std::shared_ptr<Core::ControlledActor> GetMainCharacter();
	protected:
		bool TestEvent(const Controller::Key& key, sf::Event action)const;
		void DoAction(const Controller::Key& key);

		std::map<Controller::Key, std::function<void(std::shared_ptr<Core::ControlledActor>)>> _actions;
		std::shared_ptr<Core::ControlledActor> _main_character;
	};
}