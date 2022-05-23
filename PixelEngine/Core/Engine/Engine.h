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
//#define CREATE_ACTOR(_actorclass,actorsettings,texturesettings,...)_world->SpawnActor<_actorclass>(_world.get(),actorsettings,texturesettings,##__VA_ARGS__);
//#define CREATE_ANIMATED_ACTOR(_actorclass,actorsettings,texturesettings,animationsettings,...)_world->SpawnControlledActor<_actorclass>(_world.get(),actorsettings,texturesettings,animationsettings,##__VA_ARGS__);
namespace Core {
	class Engine{
	public:
		Engine();
		Engine(const Engine&) = delete;
		Engine(Engine&&) = delete;
		Engine& operator=(const Engine&) = delete;
		Engine& operator=(Engine&&) = delete;
		virtual ~Engine();
	protected:
		std::unique_ptr<WorldBase> _CurrentWorld;
		std::queue<std::unique_ptr<WorldBase>> _WorldsQueue;
		std::unique_ptr<std::thread> _TickThread;
		std::unique_ptr<sf::RenderWindow> _mainwindow;
	protected:
		sf::Clock _clock;
		Settings::EngineSettings _enginesettings;
		Settings::WindowSettings _windowsettings;
		Settings::MusicSettings _musicsettings;
		Settings::WorldSettings _worldsettings;
	private:
		void Close();
		void Render();
		void Update();
	protected:
		virtual void InitEngine();
	public:
		void PushWorldToQueue(std::unique_ptr<WorldBase>&& newworld);
	public:
		int Run();
	};
}
