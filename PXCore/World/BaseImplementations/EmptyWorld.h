#pragma once
#include "PXCore/World/WorldBase.h"
namespace Core::World {
	class EmptyWorld :public WorldBase {
	public:
		EmptyWorld(const Settings::WorldSettings& world_settings = Settings::WorldSettings(), Engine* parent = nullptr);
		// Inherited via WorldBase
		virtual void CheckQuit() override;
		virtual void Draw(sf::RenderWindow& window)override;
		virtual void CreateWorldBaseComponents() override {}
	protected:
		// Inherited via WorldBase
		virtual void DrawMap(sf::RenderWindow& window) override;
	};
}
