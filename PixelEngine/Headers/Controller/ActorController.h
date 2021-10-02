#pragma once
#include"ControllerStructs.h"
#include <map>
#include <functional>
namespace Controller{
	class ActorController{
	public:
		ActorController(std::map<Key, std::function<void()>> actions);
	public:
		static bool TestEvent(const Key& k, sf::Event e);
		void DoAction(const Key& key);
		bool ServiceInput(sf::Event e);
	protected:
		std::map<Key, std::function<void()>> _actions;
	};
}
