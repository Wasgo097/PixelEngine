#include "EmptyWorld.h"
#include "Utility/CommonHeaders.h"
void Core::EmptyWorld::CheckQuit(){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		_quit = true;
		std::cout << "Escape pressed, empty level is quit\n";
	}
}

void Core::EmptyWorld::InitWorld(){
	std::cout << "Init empty world\n";
}

void Core::EmptyWorld::EndWorld(){
	std::cout << "End empty world\n";
}
