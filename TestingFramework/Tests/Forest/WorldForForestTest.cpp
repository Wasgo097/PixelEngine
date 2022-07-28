#include "WorldForForestTest.h"
#include "PXFactory/SettingsFactory.h"
#include "PXCore/World/Components/FpsCounter.h"
#include "ControllerForForestTest.h"
#include "Actors/Tree.h"
using namespace Core;
namespace Test {
	WorldForForestTest::WorldForForestTest(const Settings::WorldSettings& worlsettings, Core::Engine* parent) :WorldBaseGUI(worlsettings, parent) {
		_main_controller = std::make_unique<Test::ControllerForForestTest>(this);
	}
	void WorldForForestTest::CheckQuit() {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			_quit = true;
	}
	void WorldForForestTest::InitWorld() {
		WorldBaseGUI::InitWorld();
		auto tree_settings = CREATE_SETTINGS(Settings::ActorSettings, "Cfg\\TreeActorSettings.json");
		auto tree_texture = CREATE_SETTINGS(Settings::TextureSettings, "Cfg\\TreeTextureSettings.json");
		SpawnActor<Tree>(tree_settings, tree_texture);
		tree_settings.position.x += 100.0f;
		SpawnActor<Tree>(tree_settings, tree_texture);
		_tree_timer = SpawnConstActor<Core::Time::TimeManager>(Settings::ActorSettings(), Settings::TextureSettings(), .5f);
	}
	void WorldForForestTest::AddTree(std::shared_ptr<Tree> tree) {
		_created_trees.push_back(tree);
		_tree_timer->AttachToSeconds(tree.get());
	}
	void WorldForForestTest::RemoveTree(std::shared_ptr<Tree> tree) {
		_created_trees.remove(tree);
		_tree_timer->DetachFromSeconds(tree.get());
	}
	void WorldForForestTest::CreateWorldBaseGUIComponents() {
		tgui::Theme theme{ "Resource\\GUI\\themes\\TransparentGrey.txt" };
		_gui_world_components.emplace_back(std::make_unique<Core::World::Component::FpsCounter>(this, &_gui, theme));
	}
	void WorldForForestTest::InitGuiSettup() {
		WorldBaseGUI::InitGuiSettup();
		DrawWorldBaseGUIComponents();
	}
}