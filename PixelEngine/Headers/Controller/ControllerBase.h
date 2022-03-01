#pragma once
#include <SFML/Window/Event.hpp>
#include "ControllerStructs.h"
#include <memory>
namespace Core {
	class Engine;
	class ControlledActor;
}
namespace Controller {
	class ControllerBase{
	public:
		ControllerBase();
		virtual ~ControllerBase() = default;
	public:
		virtual void SetMainCharacterInputBindings() = 0;
		virtual void ServiceInput(sf::Event currentevent) = 0;
		virtual std::shared_ptr<Core::ControlledActor> GetMainCharacter() = 0;
	protected:
		std::map<Controller::Key, std::function<void(std::shared_ptr<Core::ControlledActor>)>> _actions;
		Core::Engine* _engine = nullptr;
		std::shared_ptr<Core::ControlledActor> _maincharacter;
	};
}