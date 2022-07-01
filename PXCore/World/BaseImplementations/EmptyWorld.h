#pragma once
#include "World/WorldBase.h"
namespace Core::World {
	class EmptyWorld:public WorldBase{
	public:
		EmptyWorld(const Settings::WorldSettings& worlsettings = Settings::WorldSettings(), Engine* parent = nullptr);
	public:
		// Inherited via WorldBase
		virtual void InitWorld() override;
		virtual void EndWorld() override;
		virtual void CheckQuit() override;
		virtual void Draw(sf::RenderWindow& window)override;
	};
}
