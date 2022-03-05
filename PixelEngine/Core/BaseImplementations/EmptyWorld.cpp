#include "EmptyWorld.h"
#include "Utility/CommonHeaders.h"
#include"Controller/BaseImplementations/EmptyController.h"
Core::EmptyWorld::EmptyWorld(const Settings::WorldSettings& worlsettings, Engine* parrent) :WorldBase(worlsettings, parrent) {
	InitWorld();
}
void Core::EmptyWorld::CheckQuit(){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		_quit = true;
		std::cout << "Escape pressed, empty level is quit\n";
	}
}

void Core::EmptyWorld::InitWorld(){
	std::cout << "Init empty world\n";
	_maincontroller = std::make_unique<Controller::EmptyController>(this);
}

void Core::EmptyWorld::EndWorld(){
	std::cout << "End empty world\n";
}
