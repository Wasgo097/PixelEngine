#pragma once
#include <SFML/Window/Event.hpp>
#include <compare>
#include "Enums/InputEnums.h"
namespace Core::Controller{
	struct Key{
		InputType input_type;
		sf::Event::EventType event_type;
		sf::Keyboard::Key keyboard_button;
		sf::Mouse::Button mouse_button;
		auto operator<=>(const Key& rhs)const = default;
	};
}