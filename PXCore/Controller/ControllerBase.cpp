#include "ControllerBase.h"
#include <iostream>
namespace Core::Controller {
	ControllerBase::ControllerBase(){}
	void ControllerBase::ServiceInput(sf::Event current_event){
		for (const auto& [key, value] : _actions) {
			if (TestEvent(key, current_event)) {
				DoAction(key);
				break;
			}
		}
	}
	std::shared_ptr<Object::ControlledActor> ControllerBase::GetMainCharacter(){
		return _main_character;
	}
	bool ControllerBase::TestEvent(const Controller::Key& key, sf::Event action)const {
		// Mouse event
		if (key.input_type == Controller::InputType::MouseInput &&
			key.event_type == action.type &&
			key.mouse_button == action.mouseButton.button) {
			return true;
		}
		// Keyboard event
		if (key.input_type == Controller::InputType::KeyboardInput &&
			key.event_type == action.type &&
			key.keyboard_button == action.key.code) {
			return true;
		}
		//todo service joystick input here
		return false;
	}
	void ControllerBase::DoAction(const Controller::Key& key) {
		_actions[key](_main_character);
	}
}