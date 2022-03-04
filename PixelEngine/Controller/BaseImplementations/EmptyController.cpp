#include "EmptyController.h"
#include "Utility/CommonHeaders.h"
void Controller::EmptyController::SetMainCharacterInputBindings(){
	Controller::Key key;
	key._inputtype = Controller::InputType::MouseInput;
	key._eventtype = sf::Event::MouseButtonPressed;
	key._mousebutton = sf::Mouse::Left;
	_actions[key] = [](std::shared_ptr<Core::ControlledActor> _actor) {
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

void Controller::EmptyController::SetMainCharacter(){
	throw std::exception("Not implemented yet EmptyController::SetMainCharacter");
}

