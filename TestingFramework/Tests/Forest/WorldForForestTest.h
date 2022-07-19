#pragma once
#include "PXCore/World/WorldBase.h"
#include "PXCore/Time/TimeManager.h"
namespace Test {
	class WorldForForestTest :public Core::World::WorldBase{
	public:
		WorldForForestTest(const Settings::WorldSettings& worlsettings = Settings::WorldSettings(), Core::Engine* parrent = nullptr);
	public:
		virtual void CheckQuit()override;
		virtual void InitWorld()override;
		virtual void EndWorld()override;
		virtual void Draw(sf::RenderWindow& window)override;
	protected:
		std::shared_ptr< Core::Time::TimeManager> _tree_timer;
	};
}
