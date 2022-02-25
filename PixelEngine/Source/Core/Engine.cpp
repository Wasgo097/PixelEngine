#include "CommonHeaders.h"
#include "Core/Engine.h"
#include "Core/World.h"
#include "Objects/ControlledActor.h"
#include "Factory/SettingsFactory.h"
namespace Core{
	Engine::Engine(){
		_enginesettings = CREATE_SETTINGS(Settings::EngineSettings, "cfg\\Engine.json");
		std::string settingspath = "cfg\\" + _enginesettings._windowsettings;
		_windowsettings = CREATE_SETTINGS(Settings::WindowSettings, settingspath);
		settingspath = "cfg\\" + _enginesettings._musicsettings;
		_musicsettings= CREATE_SETTINGS(Settings::MusicSettings, settingspath);
		settingspath = "cfg\\" + _enginesettings._worldsettings;
		_worldsettings = CREATE_SETTINGS(Settings::WorldSettings, settingspath);
		_drawingthread = std::make_unique<std::thread>(&Engine::Run, this);
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
					if(_maincharacter->ServiceInput(event)){

					}
					else{

					}
				}
			}
			//after event handling
		}
	}
	void Engine::Run(){
		while(!_terminated && !_mainwindow->isOpen()){
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