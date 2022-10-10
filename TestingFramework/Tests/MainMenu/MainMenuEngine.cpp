#include "MainMenuEngine.h"
#include "MainMenuWorld.h"
#include "PXFactory/SettingsFactory.h"
#include "PXSerialziation/SettingsExporter.h"
#include <fstream>
namespace Test {
	MainMenuEngine::MainMenuEngine(std::optional<std::reference_wrapper<const ArgumentParser>> parser) :Engine(parser) {
	}
	void MainMenuEngine::InitEngine() {
		PushWorldToQueue(std::make_unique<MainMenuWorld>(_window_settings, _music_settings, CREATE_SETTINGS(Settings::WorldSettings, "Cfg\\" + _engine_settings.world_settings_path), this));
	}
	void MainMenuEngine::OnNewWindowSettings(const Settings::WindowSettingsDTO& new_window_settings) {
		_window_settings.display_style = new_window_settings.display_style;
		_window_settings.fps = new_window_settings.fps;
		_window_settings.video_mode = new_window_settings.video_mode;
		_window_settings.vsync = new_window_settings.vsync;
		_main_window->create(_window_settings.video_mode, _window_settings.window_name, _window_settings.display_style);
		_main_window->setFramerateLimit(_window_settings.fps);
		_main_window->setVerticalSyncEnabled(_window_settings.vsync);
		Serialization::ExportSettingsToFile("Cfg\\"+_engine_settings.window_settings_path, _window_settings);
	}
}