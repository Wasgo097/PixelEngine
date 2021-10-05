#include "CommonHeaders.h"
#include "Core/Engine.h"
#include "Core/World.h"
#include "Objects/ControlledActor.h"
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
		_windowsettings = winsett;
		_world = std::make_unique<World>(worldsett);
		_mainwindow = std::make_unique<sf::RenderWindow>(_windowsettings.GetVideoMode(), _windowsettings.GetWinName(), _windowsettings.GetStyle());
		_mainwindow->setFramerateLimit(_windowsettings.GetFps());
		_mainwindow->setVerticalSyncEnabled(_windowsettings.GetVSync());
		_drawingthread = std::make_unique<std::thread>(&Engine::Run, this);
		////music settings 
		//reader.open(settingspath + '/' + musicsettings);
		//if(!reader.good()){
		//	std::cerr << "Cant open music window file!" << std::endl;
		//	throw std::invalid_argument("Wrong path, cant open music cfg file");
		//}
		//json jsonmusic;
		//reader >> jsonmusic;
		//reader.close();
		//double master = jsonmusic["MasterVolume"];
		//double music = jsonmusic["MusicVolume"];
		//double effect = jsonmusic["EffectVolume"];
		//Settings::MusicSettings mussett(master, music, effect);
		//_musicsettings = mussett;
	}
	Engine::~Engine(){
		std::cout << "Engine destructor\n";
	}
	void Engine::Main(){
		while(_mainwindow->isOpen()){			
			{
				sf::Event event;
				while(_mainwindow->pollEvent(event)){
					if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
						Terminate();
						Wait();
						_mainwindow->close();
					}
					if(_maincharacter->ServiceInput(event));
				}
			}
			//after event handling
		}
	}
	void Engine::Run(){
		while(_terminated || !_mainwindow->isOpen()){
			_mainwindow->clear();
			_world->Draw(*_mainwindow);
			_mainwindow->display();
		}
	}
	void Engine::Wait(){
		if(_drawingthread->joinable())
			_drawingthread->join();
	}
	void Engine::Terminate(){
		_terminated = true;
	}
}