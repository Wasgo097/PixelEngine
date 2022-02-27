#pragma once
#include "Settings/EngineSettings.h"
#include "Settings/WindowSettings.h"
#include "Settings/WorldSettings.h"
#include "Settings/MusicSettings.h"
#include "Types/ILoopingThread.h"
namespace sf {
	class RenderWindow;
}
#define CREATE_ACTOR(_actorclass,actorsettings,texturesettings,...)_world->SpawnActor<_actorclass>(_world.get(),actorsettings,texturesettings,##__VA_ARGS__);
#define CREATE_ANIMATED_ACTOR(_actorclass,actorsettings,texturesettings,animationsettings,...)_world->SpawnControlledActor<_actorclass>(_world.get(),actorsettings,texturesettings,animationsettings,##__VA_ARGS__);
#define CREATE_CONTROLLED_ACTOR(_actorclass,actorsettings,texturesettings,animationsettings,...)_world->SpawnControlledActor<_actorclass>(_world.get(),actorsettings,texturesettings,animationsettings,##__VA_ARGS__);
namespace Core {
	class World;
	class ControlledActor;
	class Engine:public Types::ILoopingThread {
	public:
		Engine();
		Engine(const Engine&) = delete;
		Engine(Engine&&) = delete;
		Engine& operator=(const Engine&) = delete;
		Engine& operator=(Engine&&) = delete;
		virtual ~Engine();
		virtual void Main();
	protected:
		std::shared_ptr<World> _world;
		std::unique_ptr<std::thread> _drawingthread;
		std::shared_ptr<sf::RenderWindow> _mainwindow;
		std::shared_ptr<ControlledActor> _maincharacter;
	protected:
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
	};
}
