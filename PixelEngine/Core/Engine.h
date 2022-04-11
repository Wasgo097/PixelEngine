#pragma once
#include "Settings/EngineSettings.h"
#include "Settings/WindowSettings.h"
#include "Settings/WorldSettings.h"
#include "Settings/MusicSettings.h"
#include "Types/ILoopingThread.h"
#include "Core/WorldBase.h"
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <stack>
//#define CREATE_ACTOR(_actorclass,actorsettings,texturesettings,...)_world->SpawnActor<_actorclass>(_world.get(),actorsettings,texturesettings,##__VA_ARGS__);
//#define CREATE_ANIMATED_ACTOR(_actorclass,actorsettings,texturesettings,animationsettings,...)_world->SpawnControlledActor<_actorclass>(_world.get(),actorsettings,texturesettings,animationsettings,##__VA_ARGS__);
namespace Core {
	class Engine:public Types::ILoopingThread {
	public:
		Engine();
		Engine(const Engine&) = delete;
		Engine(Engine&&) = delete;
		Engine& operator=(const Engine&) = delete;
		Engine& operator=(Engine&&) = delete;
		virtual ~Engine()=default;
	protected:
		std::stack<std::unique_ptr<WorldBase>> _worlds;
		std::unique_ptr<std::thread> _drawingthread;
		std::unique_ptr<sf::RenderWindow> _mainwindow;
	protected:
		sf::Clock _clock;
		Settings::EngineSettings _enginesettings;
		Settings::WindowSettings _windowsettings;
		Settings::MusicSettings _musicsettings;
		Settings::WorldSettings _worldsettings;
	protected:
		// Inherited via ILoopingThread
		virtual void Run() override;
		virtual void Wait() override;
		virtual void Terminate() override;
		bool _terminated = false;
	private:
		void Close();
		void Update();
	public:
		virtual void InitWorlds();
	public:
		int Main();
		void PushWorld(std::unique_ptr<WorldBase>&& newworld);
	};
}
