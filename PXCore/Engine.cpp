#include "Engine.h"
#include "Object/ControlledActor.h"
#include "PXFactory/SettingsFactory.h"
#include "Controller/ControllerBase.h"
#include "World/BaseImplementations/EmptyWorld.h"
#include <SFML/System.hpp>
#include <chrono>
#include <iostream>
#include "wtypes.h"
void GetDesktopResolution(int& horizontal, int& vertical)
{
	RECT desktop;
	// Get a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();
	// Get the size of screen to the variable desktop
	GetWindowRect(hDesktop, &desktop);
	// The top left corner will have coordinates (0,0)
	// and the bottom right corner will have coordinates
	// (horizontal, vertical)
	horizontal = desktop.right;
	vertical = desktop.bottom;
}
using namespace std::chrono_literals;
namespace Core {
	Engine::Engine() {
		_engine_settings = CREATE_SETTINGS(Settings::EngineSettings, "Cfg\\engine_settings.json");
		std::string settings_path = "Cfg\\" + _engine_settings.window_settings_path;
		_window_settings = CREATE_SETTINGS(Settings::WindowSettings, settings_path);
		settings_path = "Cfg\\" + _engine_settings.music_settings_path;
		_music_settings = CREATE_SETTINGS(Settings::MusicSettings, settings_path);
		_main_window = std::make_unique<sf::RenderWindow>(_window_settings.video_mode, _window_settings.window_name, _window_settings.display_style);
		_main_window->setVerticalSyncEnabled(_window_settings.vsync);
		if (_window_settings.fps > 1)
			_main_window->setFramerateLimit(_window_settings.fps);
		GetDesktopResolution(_monitor_resolution.x, _monitor_resolution.y);
	}
	Engine::~Engine() {
		Close();
	}
	int Engine::Run() {
		InitEngine();
		bool game_loop_condition = _main_window->isOpen() && _current_world;
		while (game_loop_condition) {
			ServiceInput();
			Render();
			Update();
			game_loop_condition = _main_window->isOpen() && _current_world;
		}
		return 1;
	}
	void Engine::ServiceInput() {
		if (_current_world) {
			sf::Event action;
			while (_main_window->pollEvent(action)) {
				if (action.type == sf::Event::Closed) {
					_current_world->EndWorld();
					Close();
				}
				_input_manager.ServiceEvent(action);
				_current_world->ServiceInput(action);
			}
			for (auto& key : _input_manager.GetClickedBtn())
				_current_world->ServiceInput(key);
			for (auto& key : _input_manager.GetReleasedBtn())
				_current_world->ServiceInput(key);
			_input_manager.ClearReleasedBtn();
		}
	}
	sf::RenderWindow* Engine::GetWindow() {
		return _main_window.get();
	}
	const sf::Vector2i& Engine::GetMonitorResolution() const {
		return _monitor_resolution;
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
	/*void Engine::InitEngine() {
		PushWorldToQueue(std::make_unique<World::EmptyWorld>(_world_settings, this));
	}*/
}