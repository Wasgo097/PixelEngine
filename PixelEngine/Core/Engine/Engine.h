#pragma once
#include "Settings/EngineSettings.h"
#include "Settings/WindowSettings.h"
#include "Settings/WorldSettings.h"
#include "Settings/MusicSettings.h"
#include "Interfaces/ILoopingThread.h"
#include "Core/World/WorldBase.h"
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <queue>
namespace Core {
	class Engine {
	public:
		Engine();
		virtual ~Engine();

		void PushWorldToQueue(std::unique_ptr<WorldBase>&& new_world);
		int Run();
	private:
		void Close();
		void Render();
		void Update();
	protected:
		virtual void InitEngine();
		std::unique_ptr<WorldBase> _current_world;
		std::queue<std::unique_ptr<WorldBase>> _worlds;
		std::unique_ptr<sf::RenderWindow> _main_window;

		sf::Clock _clock;
		Settings::EngineSettings _engine_settings;
		Settings::WindowSettings _window_settings;
		Settings::MusicSettings _music_settings;
		Settings::WorldSettings _world_settings;
	};
}
