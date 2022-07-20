#include "BaseEngine.h"
#include "PXCore/World/BaseImplementations/EmptyWorld.h"
#include "PXFactory/SettingsFactory.h"
namespace Test {
	void BaseEngine::InitEngine()
	{
		PushWorldToQueue(std::make_unique<Core::World::EmptyWorld>(CREATE_SETTINGS(Settings::WorldSettings, "Cfg\\" + _engine_settings.world_settings_path), this));
	}
}