#pragma once
#include <SFML/Window/Event.hpp>
#include <memory>
#include <map>
#include <functional>
#include "PXUtilities/ControllerStructs.h"
namespace Core::Object {
	class ControlledActor;
}
namespace Core::Controller {
	class ControllerBase {
	public:
		virtual ~ControllerBase() = default;
		virtual void InitMainCharacterInputBindings() = 0;
		virtual void InitMainCharacter() = 0;
		virtual void ServiceInput(sf::Event current_event);
		std::shared_ptr<Core::Object::ControlledActor> GetMainCharacter();
	protected:
		bool TestEvent(const Key& key, sf::Event action)const;
		void DoAction(const Key& key);

		std::map<Key, std::function<void(std::shared_ptr<Core::Object::ControlledActor>)>> _actions;
		std::shared_ptr<Core::Object::ControlledActor> _main_character;

	};
}