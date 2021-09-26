#include "Core/Engine.h"
#include "Core/World.h"
#include "Settings/WorldSettings.h"
#include "Settings/MusicSettings.h"
#include "Settings/WindowSettings.h"

namespace Core{
	Engine::Engine(std::string settingspath){
		std::ifstream reader(settingspath+"/Engine.json");
		if(!reader.good()){
			std::cerr << "Cant open engine config file!" << std::endl;
			throw std::invalid_argument("Wrong path, cant open engine cfg file");
		}
		json jsonengine;
		reader >> jsonengine;
		reader.close();
		std::string worldsettings = jsonengine["WorldSettingsPath"];
		std::string windowsettings = jsonengine["WindowSettingsPath"];
		std::string musicsettings = jsonengine["MusicSettingsPath"];
		_enginesettings = Settings::EngineSettings(windowsettings, musicsettings, worldsettings);
		std::cout << _enginesettings.ToStdString() << std::endl;
		//world settings
		reader.open(settingspath+'/'+worldsettings);
		if(!reader.good()){
			std::cerr << "Cant open world config file!" << std::endl;
			throw std::invalid_argument("Wrong path, cant open world cfg file");
		}
		json jsonworld;
		reader >> jsonworld;
		reader.close();
		size_t buffer_size = jsonworld["Buffer_size"];
		int gcfreqlv = jsonworld["GCFrequentLv"];
		int cycle = jsonworld["CycleToMove"];
		Settings::WorldSettings worldsett(buffer_size, gcfreqlv, cycle);
		std::cout << worldsett.ToStdString() << std::endl;
		//window settings
		reader.open(settingspath + '/' + windowsettings);
		if(!reader.good()){
			std::cerr << "Cant open engine window file!" << std::endl;
			throw std::invalid_argument("Wrong path, cant open window cfg file");
		}
		json jsonwindow;
		reader >> jsonwindow;
		reader.close();
		int x = jsonwindow["Videomode"]["X"];
		int y= jsonwindow["Videomode"]["Y"];
		int bits= jsonwindow["Videomode"]["Bits"];
		int fps = jsonwindow["Fps"];
		unsigned int style = jsonwindow["Style"];
		std::string winname= jsonwindow["Winname"];
		bool vsync= jsonwindow["Vsync"];
		Settings::WindowSettings winsett(sf::VideoMode(x, y, bits), fps, style, winname, vsync);
		std::cout << winsett.ToStdString() << std::endl;
		_world = std::make_unique<World>(worldsett, winsett);
		{
			//music settings 
			reader.open(settingspath + '/' + musicsettings);
			if(!reader.good()){
				std::cerr << "Cant open music window file!" << std::endl;
				throw std::invalid_argument("Wrong path, cant open music cfg file");
			}
			json jsonmusic;
			reader >> jsonmusic;
			reader.close();
			double master = jsonmusic["MasterVolume"];
			double music = jsonmusic["MusicVolume"];
			double effect = jsonmusic["EffectVolume"];
			Settings::MusicSettings musset(master, music, effect);
		}
	}
	//std::string Engine::HelloWorld(){
	//	return "Hello World";
	//}
	//void Engine::main(){
	//	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	//	sf::CircleShape shape(100.f);
	//	shape.setFillColor(sf::Color::Green);
	//	while(window.isOpen()){
	//		sf::Event event;
	//		while(window.pollEvent(event)){
	//			if(event.type == sf::Event::Closed)
	//				window.close();
	//		}
	//		window.clear();
	//		window.draw(shape);
	//		window.display();
	//	}
	//}
}