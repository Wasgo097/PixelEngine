#pragma once
#include <SFML/Window/Event.hpp>
#include <compare>
#include "Enums/InputEnums.h"
namespace Core::Controller{
	struct Key{
		InputType input_type=InputType::JoystickInput;
		sf::Event::EventType event_type=sf::Event::EventType::Closed;
		sf::Keyboard::Key keyboard_button=sf::Keyboard::Key::A;
		sf::Mouse::Button mouse_button=sf::Mouse::Button::Middle;
		bool repeatable = true;
		mutable bool consumed = false;
		auto operator<=>(const Key&)const = default;
	};
}