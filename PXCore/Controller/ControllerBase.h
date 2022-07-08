#pragma once
#include <SFML/Window/Event.hpp>
#include <memory>
#include <map>
#include <functional>
#include "PXUtilities/ControllerStructs.h"
namespace Core{
	namespace Object {
		class ControlledActor;
	}
	namespace World {
		class WorldBase;
	}
}
namespace Core::Controller {
	class ControllerBase {
	public:
		ControllerBase(Core::World::WorldBase* world_parent) :_world_parent{ world_parent } {};
		virtual ~ControllerBase() = default;
		virtual void InitMainCharacterInputBindings() = 0;
		virtual void InitMainCharacter() = 0;
		virtual void ServiceInput(const Core::Controller::Key& key);
		std::shared_ptr<Core::Object::ControlledActor> GetMainCharacter();
	protected:
		/*bool TestEvent(const Key& key, sf::Event action)const;
		void DoAction(const Key& key);*/
		std::map<Key, std::function<void(std::shared_ptr<Core::Object::ControlledActor>)>> _actions;
		std::shared_ptr<Core::Object::ControlledActor> _main_character;
		Core::World::WorldBase* _world_parent;
	};
}