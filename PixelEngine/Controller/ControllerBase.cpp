#include "ControllerBase.h"
#include "Utility/CommonHeaders.h"
namespace Controller {
	ControllerBase::ControllerBase(){
		SetMainCharacterInputBindings();
	}
	void ControllerBase::ServiceInput(sf::Event currentevent){
		for (const auto& [Key, Value] : _actions) {
			if (TestEvent(Key, currentevent)) {
				DoAction(Key);
			}
		}
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
	void ControllerBase::LoadTestActions() {
		Controller::Key key;
		key._inputtype = Controller::InputType::MouseInput;
		key._eventtype = sf::Event::MouseButtonPressed;
		key._mousebutton = sf::Mouse::Left;
		_actions[key] = [](std::shared_ptr<Core::ControlledActor> _actor){
			std::cout << "Left Button Pressed";
		};
		key._inputtype = Controller::InputType::KeyboardInput;
		key._eventtype = sf::Event::KeyPressed;
		key._keyboardbutton = sf::Keyboard::W;
		_actions[key] = [](std::shared_ptr<Core::ControlledActor> _actor) {
			std::cout << "W Pressed";
		};
		key._inputtype = Controller::InputType::KeyboardInput;
		key._eventtype = sf::Event::KeyPressed;
		key._keyboardbutton = sf::Keyboard::S;
		_actions[key] = [](std::shared_ptr<Core::ControlledActor> _actor) {
			std::cout << "S Pressed";
		};
		key._inputtype = Controller::InputType::KeyboardInput;
		key._eventtype = sf::Event::KeyPressed;
		key._keyboardbutton = sf::Keyboard::A;
		_actions[key] = [](std::shared_ptr<Core::ControlledActor> _actor) {
			std::cout << "A Pressed";
		};
		key._inputtype = Controller::InputType::KeyboardInput;
		key._eventtype = sf::Event::KeyPressed;
		key._keyboardbutton = sf::Keyboard::D;
		_actions[key] = [](std::shared_ptr<Core::ControlledActor> _actor) {
			std::cout << "D Pressed";
		};
	}
}