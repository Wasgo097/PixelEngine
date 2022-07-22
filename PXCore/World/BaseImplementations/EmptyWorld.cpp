#include "EmptyWorld.h"
#include <iostream>
#include "Controller/BaseImplementations/EmptyController.h"
namespace Core::World {
	EmptyWorld::EmptyWorld(const Settings::WorldSettings& worlsettings, Engine* parent) :WorldBase(worlsettings, parent) {
		_main_controller = std::make_unique<Controller::EmptyController>(this);
	}
	void EmptyWorld::CheckQuit() {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			_quit = true;
		}
	}

	void EmptyWorld::Draw(sf::RenderWindow& window) {
		window.clear(sf::Color::Blue);
		WorldBase::Draw(window);
	}
}
