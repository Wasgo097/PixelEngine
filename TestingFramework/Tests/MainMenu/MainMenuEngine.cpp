#include "MainMenuEngine.h"
#include "MainMenuWorld.h"
#include "PXFactory/SettingsFactory.h"
namespace Test {
	void MainMenuEngine::ApplyWindowSettings(const Settings::WindowSettingsDTO& new_settings) {
		_window_settings.display_style = new_settings.display_style;
		_window_settings.fps = new_settings.fps;
		_window_settings.video_mode = new_settings.video_mode;
		_main_window->create(_window_settings.video_mode, _window_settings.window_name, _window_settings.display_style);
		_main_window->setFramerateLimit(_window_settings.fps);
		auto modes = sf::VideoMode::getFullscreenModes();
		int x = 0;
		x--;
	}
	void MainMenuEngine::InitEngine() {
		PushWorldToQueue(std::make_unique<MainMenuWorld>(_window_settings, CREATE_SETTINGS(Settings::WorldSettings, "Cfg\\" + _engine_settings.world_settings_path), this));
	}
}