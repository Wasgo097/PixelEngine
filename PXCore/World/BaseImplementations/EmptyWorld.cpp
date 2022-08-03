#include "EmptyWorld.h"
#include "Controller/BaseImplementations/EmptyController.h"
namespace Core::World {
	EmptyWorld::EmptyWorld(const Settings::WorldSettings& world_settings, Engine* parent) :WorldBase(world_settings, parent) {
		_main_controller = std::make_unique<Controller::EmptyController>(this,world_settings);
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
