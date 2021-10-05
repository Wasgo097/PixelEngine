#pragma once
//#include "Utility/ISerializable.h"
#include "Settings/EngineSettings.h"
#include "Settings/WindowSettings.h"
namespace Core {
	class World;
	class Engine {
	private:
		std::unique_ptr<World> _world;
		Settings::EngineSettings _enginesettings;
		Settings::WindowSettings _windowsettings;
	public:
		Engine(std::string settingspath);
		Engine(const Engine&) = delete;
		Engine(Engine&&) = delete;
		Engine& operator=(const Engine&) = delete;
		Engine& operator=(Engine&&) = delete;
	protected:
		sf::RenderWindow _mainwindow;
	};
}
