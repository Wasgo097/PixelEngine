#pragma once
#include <SFML/Window/Event.hpp>
#include "ControllerStructs.h"
#include <memory>
#include <map>
#include <functional>
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
		virtual void ServiceInput(sf::Event currentevent);
		virtual std::shared_ptr<Core::ControlledActor> GetMainCharacter() = 0;
	protected:
		std::map<Controller::Key, std::function<void(std::shared_ptr<Core::ControlledActor>)>> _actions;
		Core::Engine* _engine = nullptr;
		std::shared_ptr<Core::ControlledActor> _maincharacter;
	protected:
		bool TestEvent(const Controller::Key& k, sf::Event e)const;
		void DoAction(const Controller::Key& key)const;
		void LoadTestActions();
	};
}