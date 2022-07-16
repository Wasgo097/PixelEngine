#include "EngineForAnimationTest.h"
#include "WorldForAnimationTest.h"
#include "PXFactory/SettingsFactory.h"
namespace Test {
	void EngineForAnimationTest::InitEngine(){
		PushWorldToQueue(std::make_unique<WorldForAnimationTest>(CREATE_SETTINGS(Settings::WorldSettings, "Cfg\\" + _engine_settings.world_settings_path), this));
	}
}