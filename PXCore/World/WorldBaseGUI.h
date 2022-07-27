#pragma once
#include "WorldBase.h"
#include <TGUI/TGUI.hpp>
namespace Core::World {
	class WorldBaseGUI :public WorldBase {
	public:
		WorldBaseGUI(const Settings::WorldSettings& world_settings = Settings::WorldSettings(), Engine* parent = nullptr);
		virtual void Draw(sf::RenderWindow& window)override;
		virtual void InitWorld()override;
		virtual void ServiceGUIInput(const sf::Event& action);
	protected:
		virtual bool InitGuiSettup() = 0;
		void RefreshGuiTarget();
		tgui::Gui _gui;
	};
}