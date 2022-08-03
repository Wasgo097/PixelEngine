#include "EngineForForestTest.h"
#include "WorldForForestTest.h"
#include "PXFactory/SettingsFactory.h"
namespace Test {
	void EngineForForestTest::InitEngine(){
		PushWorldToQueue(std::make_unique<WorldForForestTest>(CREATE_SETTINGS(Settings::WorldSettings, "Cfg\\" + _engine_settings.world_settings_path), this));
		Engine::InitEngine();
	}
}