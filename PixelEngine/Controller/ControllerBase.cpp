#include "ControllerBase.h"
#include "Utility/CommonHeaders.h"
namespace Controller {
	ControllerBase::ControllerBase(Core::WorldBase* world):_world(world){
		SetMainCharacterInputBindings();
	}
	void ControllerBase::ServiceInput(sf::Event currentevent){
		for (const auto& [Key, Value] : _actions) {
			if (TestEvent(Key, currentevent)) {
				DoAction(Key);
			}
		}
	}
	std::shared_ptr<Core::ControlledActor> ControllerBase::GetMainCharacter(){
		return _maincharacter;
	}
	bool ControllerBase::TestEvent(const Controller::Key& k, sf::Event e)const {
		// Mouse event
		if (k._inputtype == Controller::InputType::MouseInput &&
			k._eventtype == e.type &&
			k._mousebutton == e.mouseButton.button) {
			return true;
		}
		// Keyboard event
		if (k._inputtype == Controller::InputType::KeyboardInput &&
			k._eventtype == e.type &&
			k._keyboardbutton == e.key.code) {
			return true;
		}
		//todo service joystick input here
		return false;
	}
	void ControllerBase::DoAction(const Controller::Key& key)const {
		_actions.at(key)(_maincharacter);
	}
}