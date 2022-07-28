#pragma once
#include "WorldBase.h"
#include <TGUI/TGUI.hpp>
#include "Components/WorldBaseGUIComponent.h"
namespace Core::World {
	class WorldBaseGUI :public WorldBase {
	public:
		WorldBaseGUI(const Settings::WorldSettings& world_settings = Settings::WorldSettings(), Engine* parent = nullptr);
		virtual void Draw(sf::RenderWindow& window)override;
		virtual void Update(float delta)override;
		virtual void InitWorld()override;
		virtual void EndWorld()override;
		virtual void ServiceGUIInput(const sf::Event& action);
	protected:
		virtual void CreateWorldBaseComponents() {};
		virtual void CreateWorldBaseGUIComponents()=0;
		virtual bool InitGuiSettup() = 0;
		void DrawWorldBaseGUIComponents();
		void InitWorldBaseGUIComponents();
		void RefreshGuiTarget();
		tgui::Gui _gui;
		std::vector<std::unique_ptr<Component::WorldBaseGUIComponent>> _gui_world_components;
	};
}