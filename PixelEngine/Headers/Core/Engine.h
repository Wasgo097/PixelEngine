#pragma once
#include "CommonHeaders.h"
#include "Utility/ISerializable.h"
#include "Settings/EngineSettings.h"
//namespace Settings{
//	class EngineSettings;
//	class WindowSettings;
//	class WorldSettings;
//	class MusicSettings;
//}
namespace Core {
	class World;
	class Engine final {
	private:
		std::unique_ptr<World> _world;
		Settings::EngineSettings _enginesettings;
	public:
		Engine(std::string settingspath);
		Engine(const Engine&) = delete;
		Engine(Engine&&) = delete;
		Engine& operator=(const Engine&) = delete;
		Engine& operator=(Engine&&) = delete;
		std::string HelloWorld();
		void main();
	};
}
