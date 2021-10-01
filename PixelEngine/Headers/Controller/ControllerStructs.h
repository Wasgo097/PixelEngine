#pragma once
#include <SFML/Window/Event.hpp>
namespace Controller{
	enum InputType{
		KeyboardInput,
		MouseInput,
		JoystickInput
	};
	struct Key{
		InputType _inputtype;
		sf::Event::EventType _eventtype;
		sf::Keyboard::Key _keyboardbutton;
		sf::Mouse::Button _mousebutton;
		//for std::map as key
		bool operator<(const Key& key)const{
			return static_cast<int>(_inputtype) < static_cast<int>(key._inputtype);
		}
	};
}