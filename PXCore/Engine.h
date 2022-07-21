#pragma once
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <queue>
#include "PXSettings/EngineSettings.h"
#include "PXSettings/WindowSettings.h"
#include "PXSettings/WorldSettings.h"
#include "PXSettings/MusicSettings.h"
#include "World/WorldBase.h"
#include "Controller/InputManager.h"
namespace Core {
	class Engine {
	public:
		Engine();
		virtual ~Engine();

		void PushWorldToQueue(std::unique_ptr<World::WorldBase>&& new_world);
		int Run();
		void ServiceInput();
		sf::RenderWindow* GetWindow();
	private:
		void Close();
		void Render();
		void Update();
	protected:
		virtual void InitEngine()=0;
		std::unique_ptr<World::WorldBase> _current_world;
		std::queue<std::unique_ptr<World::WorldBase>> _worlds;
		std::unique_ptr<sf::RenderWindow> _main_window;
		Controller::InputManager _input_manager;
		sf::Clock _clock;
		Settings::EngineSettings _engine_settings;
		Settings::WindowSettings _window_settings;
		Settings::MusicSettings _music_settings;
	};
}
