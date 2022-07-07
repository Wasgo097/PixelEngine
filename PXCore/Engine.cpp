#include "Engine.h"
#include "Object/ControlledActor.h"
#include "PXFactory/SettingsFactory.h"
#include "Controller/ControllerBase.h"
#include "World/BaseImplementations/EmptyWorld.h"
#include <SFML/System.hpp>
#include <chrono>
#include <iostream>
using namespace std::chrono_literals;
namespace Core {
	Engine::Engine() {
		_engine_settings = CREATE_SETTINGS(Settings::EngineSettings, "Cfg\\engine_settings.json");
		std::string settings_path = "Cfg\\" + _engine_settings.window_settings_path;
		_window_settings = CREATE_SETTINGS(Settings::WindowSettings, settings_path);
		settings_path = "Cfg\\" + _engine_settings.music_settings_path;
		_music_settings = CREATE_SETTINGS(Settings::MusicSettings, settings_path);
		settings_path = "Cfg\\" + _engine_settings.world_settings_path;
		_world_settings = CREATE_SETTINGS(Settings::WorldSettings, settings_path);
		_main_window = std::make_unique<sf::RenderWindow>(_window_settings.video_mode, _window_settings.window_name, _window_settings.display_style);
		_main_window->setVerticalSyncEnabled(_window_settings.vsync);
		if (_window_settings.fps > 1)
			_main_window->setFramerateLimit(_window_settings.fps);
	}
	Engine::~Engine() {
		Close();
	}
	int Engine::Run() {
		InitEngine();
		bool game_loop_condition = _main_window->isOpen() && _current_world;
		while (game_loop_condition) {
			sf::Event action;
			int pool_event_size = 0;
			while (_main_window->pollEvent(action)){
				if (action.type == sf::Event::Closed) {
					_current_world->EndWorld();
					Close();
				}
				else
					_current_world->ServiceInput(action);
				pool_event_size++;
			}
			std::cout << "pool event size " << pool_event_size << std::endl;
			Render();
			Update();
			game_loop_condition = _main_window->isOpen() && _current_world;
		}
		return 1;
	}
	void Engine::PushWorldToQueue(std::unique_ptr<World::WorldBase>&& new_world) {
		if (_current_world)
			_worlds.push(std::move(new_world));
		else {
			_current_world = std::move(new_world);
			_current_world->InitWorld();
		}
	}
	void Engine::Update() {
		sf::Time time = _clock.restart();
		if (!_current_world)
			return;
		_current_world->CheckQuit();
		if (_current_world->Quit()) {
			_current_world->EndWorld();
			_current_world.reset();
			if (!_worlds.empty()) {
				_current_world = std::move(_worlds.front());
				_current_world->InitWorld();
				_worlds.pop();
			}
			else
				Close();
		}
		else
			_current_world->Update(time.asSeconds());
	}
	void Engine::Close() {
		while (!_worlds.empty())
			_worlds.pop();
		_main_window->close();
	}
	void Engine::Render() {
		_main_window->clear();
		if (_current_world)
			_current_world->Draw(*_main_window);
		_main_window->display();
	}
	void Engine::InitEngine() {
		PushWorldToQueue(std::make_unique<World::EmptyWorld>(_world_settings, this));
	}
}