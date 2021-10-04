#include "Controller/ActorController.h"
namespace Controller{
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
		/*std::map<Controller::Key, std::function<void(Core::ControlledActor*)>> & _actions = _settings.GetActions();
		_actions[key](nullptr);*/
	}
	bool ActorController::ServiceInput(sf::Event e){
	/*	std::map<Controller::Key, std::function<void(Core::ControlledActor*)>> & _actions = _settings.GetActions();
		for(const auto &[Key, Value] : _actions){
			if(TestEvent(Key, e)){
				DoAction(Key);
				return true;
			}
		}*/
		return false;
	}
}
