#include "SerialziationTest.h"
#include "Utility/CommonHeaders.h"
#include <Factory/SettingsFactory.h>
namespace Test {
	SerialziationTest::SerialziationTest(std::string rootpath) :_rootpath(rootpath) {}
	void SerialziationTest::PrepareTest() {
		//create default json files here
		std::string filepath = _rootpath + "actorsettings.json";
		CREATE_SETTINGS_FILE(filepath, _actorsettings);
		filepath = _rootpath + "animationsettings.json";
		CREATE_SETTINGS_FILE(filepath, _animationsettings);
		filepath = _rootpath + "enginesettings.json";
		CREATE_SETTINGS_FILE(filepath, _enginesettings);
		filepath = _rootpath + "musicsettings.json";
		CREATE_SETTINGS_FILE(filepath, _musicsettings);
		filepath = _rootpath + "texturesettings.json";
		CREATE_SETTINGS_FILE(filepath, _texturesettings);
		filepath = _rootpath + "windowsettings.json";
		CREATE_SETTINGS_FILE( filepath, _windowsettings);
		filepath = _rootpath + "worldsettings.json";
		CREATE_SETTINGS_FILE(filepath, _worldsettings);
	}
	bool SerialziationTest::RunTest() {
		try {
			PrepareTest();
			std::string filepath = _rootpath + "actorsettings.json";
			auto actorsettings = CREATE_SETTINGS(ActorSettings, filepath);
			filepath = _rootpath + "animationsettings.json";
			auto animationsettings = CREATE_SETTINGS(AnimationSettings, filepath);
			filepath = _rootpath + "enginesettings.json";
			auto enginesettings = CREATE_SETTINGS(EngineSettings, filepath);
			filepath = _rootpath + "musicsettings.json";
			auto musicsettings = CREATE_SETTINGS(MusicSettings, filepath);
			filepath = _rootpath + "texturesettings.json";
			auto texturesettings = CREATE_SETTINGS(TextureSettings, filepath);
			filepath = _rootpath + "windowsettings.json";
			auto windowsettings = CREATE_SETTINGS(WindowSettings, filepath);
			filepath = _rootpath + "worldsettings.json";
			auto worldsettings = CREATE_SETTINGS(WorldSettings, filepath);
			return _actorsettings == actorsettings && _animationsettings == animationsettings && _enginesettings == enginesettings && 
				musicsettings == _musicsettings && _texturesettings == texturesettings && _windowsettings == windowsettings	&& _worldsettings == worldsettings;
		}
		catch (...) {
			return false;
		}
		return true;
	}
}