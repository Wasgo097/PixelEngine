#include "WorldBaseGUI.h"
#include "Engine.h"
namespace Core::World {
	WorldBaseGUI::WorldBaseGUI(const Settings::WorldSettings& world_settings, Engine* parent) :WorldBase(world_settings, parent) {
		RefreshGuiTarget();
	}
	void WorldBaseGUI::Draw(sf::RenderWindow& window) {
		WorldBase::Draw(window);
		_gui.draw();
	}
	void WorldBaseGUI::Update(float delta) {
		WorldBase::Update(delta);
		for (const auto& component : _gui_world_components)
			if (component->TickFlag())
				component->Tick(delta);
	}
	void WorldBaseGUI::InitWorld() {
		WorldBase::InitWorld();
		try {
			CreateWorldBaseGUIComponents();
			InitWorldBaseGUIComponents();
			InitGuiSettup();
			_initialized = true;
		}
		catch (std::exception& ex) {
			std::cerr << "WorldBaseGUI::InitWorld exception " << ex.what() << std::endl;
			_initialized = false;
		}
	}
	void WorldBaseGUI::DrawWorldBaseGUIComponents() {
		for (const auto& component : _gui_world_components)
			component->Draw();
	}
	void WorldBaseGUI::InitWorldBaseGUIComponents() {
		for (const auto& component : _gui_world_components)
			component->InitComponent();
	}
	void WorldBaseGUI::InitGuiSettup() {
		_gui.removeAllWidgets();
	}
	void WorldBaseGUI::EndWorld() {
		WorldBase::EndWorld();
		for (const auto& component : _gui_world_components)
			component->EndComponent();
	}
	void WorldBaseGUI::ServiceGUIInput(const sf::Event& action) {
		_gui.handleEvent(action);
	}
	void WorldBaseGUI::RefreshGuiTarget() {
		_gui.setTarget(*_parent->GetWindow());
	}
}