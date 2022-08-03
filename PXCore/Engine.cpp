#include "Engine.h"
#include "Object/ControlledActor.h"
#include "PXFactory/SettingsFactory.h"
#include "Controller/ControllerBase.h"
#include "World/BaseImplementations/EmptyWorld.h"
#include "World/WorldBaseGUI.h"
#include <SFML/System.hpp>
#include <chrono>
using namespace std::chrono_literals;
namespace Core {
	Engine::Engine(std::optional<std::reference_wrapper<const ArgumentParser>> parser) :_parser{ parser } {
		_engine_settings = CREATE_SETTINGS(Settings::EngineSettings, "Cfg\\engine_settings.json");
		std::string settings_path = "Cfg\\" + _engine_settings.window_settings_path;
		_window_settings = CREATE_SETTINGS(Settings::WindowSettings, settings_path);
		settings_path = "Cfg\\" + _engine_settings.music_settings_path;
		_music_settings = CREATE_SETTINGS(Settings::MusicSettings, settings_path);
		_main_window = std::make_unique<sf::RenderWindow>(_window_settings.video_mode, _window_settings.window_name, _window_settings.display_style);
		_main_window->setVerticalSyncEnabled(_window_settings.vsync);
		if (_window_settings.fps > 1)
			_main_window->setFramerateLimit(_window_settings.fps);
		_view.setSize(static_cast<float>(_window_settings.video_mode.width), static_cast<float>(_window_settings.video_mode.height));
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
				if (auto gui_world = dynamic_cast<World::WorldBaseGUI*>(_current_world.get()); gui_world)
					gui_world->ServiceGUIInput(action);
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
	std::optional<std::reference_wrapper<const ArgumentParser>> Engine::GetParser() const {
		return _parser;
	}
	void Engine::RefreshView(const sf::Vector2f& center) {
		_view.setCenter(center);
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
		else {
			_current_world->Update(time.asSeconds());
		}
	}
	void Engine::InitEngine() {
		_view = sf::View({ .0f,.0f }, { static_cast<float>(_window_settings.video_mode.height),static_cast<float>(_window_settings.video_mode.height) });
		if (auto center = _current_world->GetMainCharacterPosition(); center)
			_view.setCenter(*center);
	}
	void Engine::Close() {
		while (!_worlds.empty())
			_worlds.pop();
		_main_window->close();
	}
	void Engine::Render() {
		_main_window->setView(_view);
		_main_window->clear();
		if (_current_world)
			_current_world->Draw(*_main_window);
		_main_window->display();
	}
}