#pragma once
#include"ControllerStructs.h"
#include <map>
#include <functional>
namespace Controller{
	class ActorController{
	public:
		ActorController(std::map<Key, std::function<void()>> actions);
	protected:
		std::map<Key, std::function<void()>> _actions;
	public:
		static bool TestEvent(const Key& k, sf::Event e){
			// Mouse event
			if(k._inputtype == MouseInput &&
				k._eventtype == e.type &&
				k._mousebutton == e.mouseButton.button){
				return true;
			}
			// Keyboard event
			if(k._inputtype == KeyboardInput &&
				k._eventtype == e.type &&
				k._keyboardbutton == e.key.code){
				return true;
			}
			//todo service joystick input here
			return false;
		}
		void DoAction(const Key& key){
			_actions[key]();
		}
		bool ServiceInput(sf::Event e){
			for(const auto &[Key, Value] : _actions){
				if(TestEvent(Key, e)){
					DoAction(Key);
					return true;
				}
			}
			return false;
		}
	};
}
