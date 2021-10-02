#include "Controller/ActorController.h"
namespace Controller{
	ActorController::ActorController(std::map<Key, std::function<void()>> actions) :_actions(std::move(actions)){}
	bool ActorController::TestEvent(const Key & k, sf::Event e){
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
	void ActorController::DoAction(const Key & key){
		_actions[key]();
	}
	bool ActorController::ServiceInput(sf::Event e){
		for(const auto &[Key, Value] : _actions){
			if(TestEvent(Key, e)){
				DoAction(Key);
				return true;
			}
		}
		return false;
	}
}
