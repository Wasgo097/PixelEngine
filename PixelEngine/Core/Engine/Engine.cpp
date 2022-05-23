#include "Utility/CommonHeaders.h"
#include "Engine.h"
#include "Core/World/WorldBase.h"
#include "Objects/ControlledActor.h"
#include "Factory/SettingsFactory.h"
#include "Controller/ControllerBase.h"
#include "Core/World/BaseImplementations/EmptyWorld.h"
#include <SFML/System.hpp>
#include <chrono>
using namespace std::chrono_literals;
namespace Core {
	Engine::Engine() {
		_enginesettings = CREATE_SETTINGS(Settings::EngineSettings, "Cfg\\enginesettings.json");
		std::string settingspath = "Cfg\\" + _enginesettings._windowsettings;
		_windowsettings = CREATE_SETTINGS(Settings::WindowSettings, settingspath);
		settingspath = "Cfg\\" + _enginesettings._musicsettings;
		_musicsettings = CREATE_SETTINGS(Settings::MusicSettings, settingspath);
		settingspath = "Cfg\\" + _enginesettings._worldsettings;
		_worldsettings = CREATE_SETTINGS(Settings::WorldSettings, settingspath);
		_mainwindow = std::make_unique<sf::RenderWindow>(_windowsettings._videomode, _windowsettings._winname, _windowsettings._style);
		_mainwindow->setVerticalSyncEnabled(_windowsettings._vsync);
		if (_windowsettings._fps > 1)
			_mainwindow->setFramerateLimit(_windowsettings._fps);
	}
	Engine::~Engine() {
		Close();
	}
	int Engine::Run() {
		InitEngine();
		bool GameLoopConditional = _mainwindow->isOpen() && _CurrentWorld;
		while (GameLoopConditional) {
			sf::Event event;
			while (_mainwindow->pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					_CurrentWorld->EndWorld();
					Close();
				}
				else
					_CurrentWorld->ServiceInput(event);
			}
			Render();
			Update();
			GameLoopConditional = _mainwindow->isOpen() && _CurrentWorld;
		}
		return 1;
	}
	void Engine::PushWorldToQueue(std::unique_ptr<WorldBase>&& newworld) {
		if (_CurrentWorld)
			_WorldsQueue.push(std::move(newworld));
		else {
			_CurrentWorld = std::move(newworld);
			_CurrentWorld->InitWorld();
		}
	}
	void Engine::Update() {
		sf::Time time = _clock.restart();
		if (_CurrentWorld) {
			_CurrentWorld->CheckQuit();
			if (_CurrentWorld->Quit()) {
				_CurrentWorld->EndWorld();
				_CurrentWorld.reset();
				if (!_WorldsQueue.empty()) {
					_CurrentWorld = std::move(_WorldsQueue.front());
					_CurrentWorld->InitWorld();
					_WorldsQueue.pop();
				}
				else
					Close();
			}
			else
				_CurrentWorld->Update(time.asSeconds());
		}
	}
	void Engine::Close() {
		while (!_WorldsQueue.empty())
			_WorldsQueue.pop();
		_mainwindow->close();
	}
	void Engine::Render() {
		_mainwindow->clear();
		if (_CurrentWorld)
			_CurrentWorld->Draw(*_mainwindow);
		_mainwindow->display();
	}
	void Engine::InitEngine() {
		PushWorldToQueue(std::make_unique<EmptyWorld>(_worldsettings, this));
	}
}