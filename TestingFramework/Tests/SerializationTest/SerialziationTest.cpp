#include "SerialziationTest.h"
#include "Utility/CommonHeaders.h"
#include "Factory/SettingsFactory.h"
namespace Test {
	SerialziationTest::SerialziationTest(std::string rootpath) :_rootpath(rootpath) {}
	void SerialziationTest::PrepareTest() {
		//create default json files here
		std::string filepath = _rootpath + "actorsettings.json";
		CREATE_SETTINGS_FILE(_actor_settings, filepath);
		filepath = _rootpath + "animationsettings.json";
		CREATE_SETTINGS_FILE(_animation_settings, filepath);
		filepath = _rootpath + "enginesettings.json";
		CREATE_SETTINGS_FILE(_engine_settings, filepath);
		filepath = _rootpath + "musicsettings.json";
		CREATE_SETTINGS_FILE(_music_settings, filepath);
		filepath = _rootpath + "texturesettings.json";
		CREATE_SETTINGS_FILE(_texture_settings, filepath);
		filepath = _rootpath + "windowsettings.json";
		CREATE_SETTINGS_FILE(_window_settings, filepath);
		filepath = _rootpath + "worldsettings.json";
		CREATE_SETTINGS_FILE(_world_settings, filepath);
	}
	bool SerialziationTest::RunTest() {
		try {
			PrepareTest();
			std::string file_path = _rootpath + "actorsettings.json";
			auto actor_settings = CREATE_SETTINGS(ActorSettings, file_path);
			file_path = _rootpath + "animationsettings.json";
			auto animation_settings = CREATE_SETTINGS(AnimationSettings, file_path);
			file_path = _rootpath + "enginesettings.json";
			auto engine_settings = CREATE_SETTINGS(EngineSettings, file_path);
			file_path = _rootpath + "musicsettings.json";
			auto music_settings = CREATE_SETTINGS(MusicSettings, file_path);
			file_path = _rootpath + "texturesettings.json";
			auto texture_settings = CREATE_SETTINGS(TextureSettings, file_path);
			file_path = _rootpath + "windowsettings.json";
			auto window_settings = CREATE_SETTINGS(WindowSettings, file_path);
			file_path = _rootpath + "worldsettings.json";
			auto world_settings = CREATE_SETTINGS(WorldSettings, file_path);
			return _actor_settings == actor_settings && _animation_settings == animation_settings && _engine_settings == engine_settings &&
				_music_settings == music_settings && _texture_settings == texture_settings && _window_settings == window_settings && _world_settings == world_settings;
		}
		catch (...) {
			return false;
		}
		return true;
	}
}