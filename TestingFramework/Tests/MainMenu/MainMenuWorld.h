#pragma once
#include "PXCore/World/WorldBase.h"
#include <TGUI/TGUI.hpp>
namespace Test {
	class MainMenuWorld :public Core::World::WorldBase {
	public:
		MainMenuWorld(const Settings::WorldSettings& world_settings = Settings::WorldSettings(), Core::Engine* parent = nullptr);
		virtual void Draw(sf::RenderWindow& window)override;
		virtual void ServiceInput(const sf::Event& action) {};
	protected:
		// Inherited via WorldBase
		virtual void CheckQuit() override;
		virtual void InitWorld()override;
		tgui::Gui _gui;
	};
}