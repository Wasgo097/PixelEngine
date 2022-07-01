#include "EmptyWorld.h"
#include "Utility/CommonHeaders.h"
#include "Controller/BaseImplementations/EmptyController.h"
Core::EmptyWorld::EmptyWorld(const Settings::WorldSettings& worlsettings, Engine* parent) :WorldBase(worlsettings, parent) {
	_main_controller = std::make_unique<Controller::EmptyController>(this);
}
void Core::EmptyWorld::CheckQuit(){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		_quit = true;
		std::cout << "Escape pressed, empty world is quit\n";
	}
}

void Core::EmptyWorld::Draw(sf::RenderWindow& window)
{
	window.clear(sf::Color::Blue);
	WorldBase::Draw(window);
}

void Core::EmptyWorld::InitWorld(){
	WorldBase::InitWorld();
	std::cout << "Init empty world\n";
}

void Core::EmptyWorld::EndWorld(){
	WorldBase::EndWorld();
	std::cout << "End empty world\n";
}
