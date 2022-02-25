#include "SerialziationTest.h"
#include "CommonHeaders.h"
#include <Factory/SettingsFactory.h>
namespace Test {
	SerialziationTest::SerialziationTest(std::string rootpath) :_rootpath(rootpath) {}
	void SerialziationTest::PrepareTest() {
		//create default json files here
		std::string filepath = _rootpath + "_actorsettings.json";
		CREATE_SETTINGS_FILE(ActorSettings, filepath, _actorsettings);
		filepath = _rootpath + "_animationsettings.json";
		CREATE_SETTINGS_FILE(AnimationSettings, filepath, _animationsettings);
		filepath = _rootpath + "_enginesettings.json";
		CREATE_SETTINGS_FILE(EngineSettings, filepath, _enginesettings);
		filepath = _rootpath + "_musicsettings.json";
		CREATE_SETTINGS_FILE(MusicSettings, filepath, _musicsettings);
		filepath = _rootpath + "_texturesettings.json";
		CREATE_SETTINGS_FILE(TextureSettings, filepath, _texturesettings);
		filepath = _rootpath + "_windowsettings.json";
		CREATE_SETTINGS_FILE(WindowSettings, filepath, _windowsettings);
		filepath = _rootpath + "_worldsettings.json";
		CREATE_SETTINGS_FILE(WorldSettings, filepath, _worldsettings);
	}
	bool SerialziationTest::RunTest() {
		try {
			PrepareTest();
			std::string filepath = _rootpath + "_actorsettings.json";
			auto actorsettings = CREATE_SETTINGS(ActorSettings, filepath);
			filepath = _rootpath + "_animationsettings.json";
			auto animationsettings = CREATE_SETTINGS(AnimationSettings, filepath);
			filepath = _rootpath + "_enginesettings.json";
			auto enginesettings = CREATE_SETTINGS(EngineSettings, filepath);
			filepath = _rootpath + "_musicsettings.json";
			auto musicsettings = CREATE_SETTINGS(MusicSettings, filepath);
			filepath = _rootpath + "_texturesettings.json";
			auto texturesettings = CREATE_SETTINGS(TextureSettings, filepath);
			filepath = _rootpath + "_windowsettings.json";
			auto windowsettings = CREATE_SETTINGS(WindowSettings, filepath);
			filepath = _rootpath + "_worldsettings.json";
			auto worldsettings = CREATE_SETTINGS(WorldSettings, filepath);
		}
		catch (...) {
			return false;
		}
		return true;
	}
}