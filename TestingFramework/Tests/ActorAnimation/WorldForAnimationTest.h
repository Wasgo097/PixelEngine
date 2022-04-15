#pragma once
#include "Core/World/WorldBase.h"
namespace Test {
	class WorldForAnimationTest:public Core::WorldBase
	{
	public:
		WorldForAnimationTest(const Settings::WorldSettings& worlsettings = Settings::WorldSettings(), Core::Engine* parrent = nullptr);
	public:
		virtual void CheckQuit()override;
		virtual void InitWorld()override;
		virtual void EndWorld()override;
	};
}
