#include "CommonHeaders.h"
#include "Core/Engine.h"
#include "Core/World.h"
#include "Objects/ControlledActor.h"
#include "Factory/SettingsFactory.h"
#include <SFML/System.hpp>
namespace Core {
	Engine::Engine() {
		_enginesettings = CREATE_SETTINGS(Settings::EngineSettings, "cfg\\enginesettings.json");
		std::string settingspath = "cfg\\" + _enginesettings._windowsettings;
		_windowsettings = CREATE_SETTINGS(Settings::WindowSettings, settingspath);
		settingspath = "cfg\\" + _enginesettings._musicsettings;
		_musicsettings = CREATE_SETTINGS(Settings::MusicSettings, settingspath);
		settingspath = "cfg\\" + _enginesettings._worldsettings;
		_worldsettings = CREATE_SETTINGS(Settings::WorldSettings, settingspath);
		_mainwindow = std::make_unique<sf::RenderWindow>(_windowsettings._videomode, _windowsettings._winname, _windowsettings._style);
		_mainwindow->setVerticalSyncEnabled(_windowsettings._vsync);
		if (_windowsettings._fps > 1)
			_mainwindow->setFramerateLimit(_windowsettings._fps);
		_mainwindow->setActive(false);
		_drawingthread = std::make_unique<std::thread>(std::bind(&Engine::Run, this));
		_world = std::make_shared<World>(_worldsettings);
	}
	Engine::~Engine() {
		if (_world)
			_world->WaitOnActorManager();
		//std::cout << "Engine destructor\n";
	}
	void Engine::Main() {
		while (_mainwindow->isOpen()) {
			sf::Event event;
			while (_mainwindow->pollEvent(event)) {
				if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
					Close();
				else if (_maincharacter && _maincharacter->ServiceInput(event)) {

				}
				else {

				}
			}
			//after event handling
			Update();
		}
	}
	void Engine::Run() {
		_mainwindow->setActive(true);
		while (!_terminated && _mainwindow->isOpen()) {
			_mainwindow->clear(sf::Color::Blue);
			if (_world)
				_world->Draw(*_mainwindow);
			_mainwindow->display();
		}
		_mainwindow->setActive(false);
	}
	void Engine::Wait() {
		if (_drawingthread->joinable())
			_drawingthread->join();
	}
	void Engine::Terminate() {
		_terminated = true;
	}
	void Engine::Close(){
		Terminate();
		Wait();
		_mainwindow->setActive(true);
		_mainwindow->close();
		if (_world)
			_world->TermianateActorManager();
	}
	void Engine::Update()	{
		sf::Time time = _clock.restart();
		_world->Update(time.asSeconds());
	}
}