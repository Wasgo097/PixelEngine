#pragma once
#include "Settings/EngineSettings.h"
#include "Settings/WindowSettings.h"
#include "Settings/WorldSettings.h"
#include "Settings/MusicSettings.h"
#include "Types/ILoopingThread.h"
namespace Core {
	class World;
	class ControlledActor;
	class Engine:public Types::ILoopingThread {
	public:
		Engine(std::string settingspath);
		Engine(const Engine&) = delete;
		Engine(Engine&&) = delete;
		Engine& operator=(const Engine&) = delete;
		Engine& operator=(Engine&&) = delete;
		virtual ~Engine();
		virtual void Main();
	protected:
		std::unique_ptr<World> _world;
		std::unique_ptr<std::thread> _drawingthread;
		std::unique_ptr<sf::RenderWindow> _mainwindow;
		std::shared_ptr<ControlledActor> _maincharacter;
		Settings::EngineSettings _enginesettings;
		Settings::WindowSettings _windowsettings;
		//Settings::MusicSettings _musicsettings;
	protected:
		// Inherited via ILoopingThread
		virtual void Run() override;
		virtual void Wait() override;
		virtual void Terminate() override;
		bool _terminated = false;
	};
}
