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
		if ((_actor_manager and !_main_controller) and InitGuiSettup())
			_initialized = true;
		for (const auto& component : _gui_world_components)
				component->InitComponent();
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