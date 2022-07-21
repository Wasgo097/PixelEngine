#include "MainMenuEngine.h"
#include "MainMenuWorld.h"
#include "PXFactory/SettingsFactory.h"
namespace Test {
	void MainMenuEngine::InitEngine() {
		PushWorldToQueue(std::make_unique<MainMenuWorld>(CREATE_SETTINGS(Settings::WorldSettings, "Cfg\\" + _engine_settings.world_settings_path), this));
		_main_window->setTitle("Main Menu");
	}
}