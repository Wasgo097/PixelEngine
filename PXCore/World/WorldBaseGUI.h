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
		template<typename T>
			requires std::derived_from<T, Component::WorldBaseGUIComponent>
		std::shared_ptr<T> GetTGuiComponent()const {
			for (const auto& component : _gui_world_components) {
				if (auto casted_component = std::dynamic_pointer_cast<T>(component); casted_component)
					return casted_component;
			}
			return {};
		}
		virtual void CreateWorldBaseComponents() {};
		virtual void CreateWorldBaseGUIComponents() = 0;
		virtual void InitGuiSettup();
		void DrawWorldBaseGUIComponents();
		void InitWorldBaseGUIComponents();
		void RefreshGuiTarget();
		tgui::Gui _gui;
		std::list<std::shared_ptr<Component::WorldBaseGUIComponent>> _gui_world_components;
	};
}