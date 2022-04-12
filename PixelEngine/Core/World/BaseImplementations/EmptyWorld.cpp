#include "EmptyWorld.h"
#include "Utility/CommonHeaders.h"
#include"Controller/BaseImplementations/EmptyController.h"
Core::EmptyWorld::EmptyWorld(const Settings::WorldSettings& worlsettings, Engine* parrent) :WorldBase(worlsettings, parrent) {
	_maincontroller = std::make_unique<Controller::EmptyController>(this);
	_maincontroller->InitMainCharacterInputBindings();
	_maincontroller->InitMainCharacter();
}
void Core::EmptyWorld::CheckQuit(){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		_quit = true;
		std::cout << "Escape pressed, empty level is quit\n";
	}
}

void Core::EmptyWorld::InitWorld(){
	WorldBase::InitWorld();
	std::cout << "Init empty world\n";
}

void Core::EmptyWorld::EndWorld(){
	WorldBase::EndWorld();
	std::cout << "End empty world\n";
}
