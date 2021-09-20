#include "Core/Engine.h"
#include "Core/World.h"
#include "Settings/WorldSettings.h"
#include "Settings/MusicSettings.h"
#include "Settings/WindowSettings.h"
namespace Core{
	Engine::Engine(std::string settingspath){
		std::ifstream reader(settingspath);
		if(!reader.good()){
			std::cerr << "Cant open engine config file!" << std::endl;
			return;
		}
		json jsondata;
		reader >> jsondata;
		reader.close();
		std::string worldsettings = jsondata["WorldSettingsPath"];
		std::string windowsettings = jsondata["WindowSettingsPath"];
		std::string musicsettings = jsondata["MusicSettingsPath"];
		_enginesettings = Settings::EngineSettings(windowsettings, musicsettings, worldsettings);
		std::cout << _enginesettings.ToStdString() << std::endl;
	}
	std::string Engine::HelloWorld(){
		return "Hello World";
	}
	void Engine::main(){
		sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
		sf::CircleShape shape(100.f);
		shape.setFillColor(sf::Color::Green);
		while(window.isOpen()){
			sf::Event event;
			while(window.pollEvent(event)){
				if(event.type == sf::Event::Closed)
					window.close();
			}
			window.clear();
			window.draw(shape);
			window.display();
		}
	}
}