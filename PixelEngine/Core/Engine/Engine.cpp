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
	int Engine::Main() {
		InitEngine();
		bool GameLoopConditional = false;
		{
			//std::lock_guard lock(_CurrentWorld.Mtx);
			GameLoopConditional = _mainwindow->isOpen() && _CurrentWorld.Rsc;
		}
		while (GameLoopConditional) {
			sf::Event event;
			while (_mainwindow->pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					_CurrentWorld.Rsc->EndWorld();
					Close();
				}
				else {
					//std::lock_guard lock(_CurrentWorld.Mtx);
					_CurrentWorld.Rsc->ServiceInput(event);
				}
			}
			Render();
			Update();
			//std::lock_guard lock(_CurrentWorld.Mtx);
			GameLoopConditional = _mainwindow->isOpen() && _CurrentWorld.Rsc;
		}
		return 1;
	}
	void Engine::PushWorldToQueue(std::unique_ptr<WorldBase>&& newworld) {
		//std::lock_guard lock(_CurrentWorld.Mtx);
		if (_CurrentWorld.Rsc) {
			//std::lock_guard lock(_WorldsQueue.Mtx);
			_WorldsQueue.Rsc.push(std::move(newworld));
		}
		else {
			_CurrentWorld.Rsc = std::move(newworld);
			_CurrentWorld.Rsc->InitWorld();
		}
	}
	void Engine::Update() {
		sf::Time time = _clock.restart();
		//std::lock_guard lock(_CurrentWorld.Mtx);
		if (_CurrentWorld.Rsc) {
			_CurrentWorld.Rsc->CheckQuit();
			if (_CurrentWorld.Rsc->Quit()) {
				_CurrentWorld.Rsc->EndWorld();
				_CurrentWorld.Rsc.reset();
				//std::lock_guard lock2(_WorldsQueue.Mtx);
				if (!_WorldsQueue.Rsc.empty()) {
					_CurrentWorld.Rsc = std::move(_WorldsQueue.Rsc.front());
					_CurrentWorld.Rsc->InitWorld();
					_WorldsQueue.Rsc.pop();
				}
				else
					Close();
			}
			else
				_CurrentWorld.Rsc->Update(time.asSeconds());
		}
	}
	void Engine::Close() {
		while (!_WorldsQueue.Rsc.empty())
			_WorldsQueue.Rsc.pop();
		_mainwindow->close();
	}
	void Engine::Render() {
		_mainwindow->clear();
		{
			//std::lock_guard lock(_CurrentWorld.Mtx);
			if (_CurrentWorld.Rsc)
				_CurrentWorld.Rsc->Draw(*_mainwindow);
		}
		_mainwindow->display();
	}
	void Engine::InitEngine() {
		PushWorldToQueue(std::make_unique<EmptyWorld>(_worldsettings, this));
	}
}