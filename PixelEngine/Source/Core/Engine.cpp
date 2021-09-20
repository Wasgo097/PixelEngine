#include "Core/Engine.h"
#include "Core/World.h"
#include "Settings/WorldSettings.h"
#include "Settings/MusicSettings.h"
#include "Settings/WindowSettings.h"
namespace Core {
	Engine::Engine(std::string settingspath){
		std::ifstream reader(settingspath);
		json jsondata;
		reader >> jsondata;
		reader.close();
	}
	std::string Engine::HelloWorld () {
		return "Hello World";
	}
	void Engine::main () {
		sf::RenderWindow window (sf::VideoMode (200, 200), "SFML works!");
		sf::CircleShape shape (100.f);
		shape.setFillColor (sf::Color::Green);
		while( window.isOpen () ) {
			sf::Event event;
			while( window.pollEvent (event) ) {
				if( event.type == sf::Event::Closed )
					window.close ();
			}
			window.clear ();
			window.draw (shape);
			window.display ();
		}
	}
}