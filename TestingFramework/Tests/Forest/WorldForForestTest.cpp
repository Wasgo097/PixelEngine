#include "WorldForForestTest.h"
#include <iostream>
#include "ControllerForForestTest.h"
#include "Actors/Tree.h"
#include "PXFactory/SettingsFactory.h"
using namespace Core;
namespace Test {
	WorldForForestTest::WorldForForestTest(const Settings::WorldSettings& worlsettings, Core::Engine* parent) :WorldBase(worlsettings, parent) {
		_main_controller = std::make_unique<Test::ControllerForForestTest>(this);
	}
	void WorldForForestTest::CheckQuit() {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			_quit = true;
			std::cout << "Escape pressed, WorldForForestTest is quit\n";
		}
	}
	void WorldForForestTest::InitWorld() {
		WorldBase::InitWorld();
		auto tree_settings = CREATE_SETTINGS(Settings::ActorSettings, "Cfg\\TreeActorSettings.json");
		auto tree_texture = CREATE_SETTINGS(Settings::TextureSettings, "Cfg\\TreeTextureSettings.json");
		//SpawnActor<Tree>(tree_settings, tree_texture);
		tree_settings.position.x += (96 * 2);
		tree_settings.position.y += 96;
		SpawnActor<Tree>(tree_settings, tree_texture);
		_tree_timer = SpawnConstActor<Core::Time::TimeManager>(Settings::ActorSettings(), Settings::TextureSettings(), .5f);
		std::cout << "Init WorldForForestTest world\n";
	}
	void WorldForForestTest::EndWorld() {
		WorldBase::EndWorld();
		std::cout << "End WorldForForestTest world\n";
	}
	void WorldForForestTest::Draw(sf::RenderWindow& window) {
		window.clear(sf::Color::Green);
		WorldBase::Draw(window);
	}
	void WorldForForestTest::AddTree(std::shared_ptr<Tree> tree){
		_created_trees.push_back(tree);
		_tree_timer->AttachToSeconds(tree.get());
	}
	void WorldForForestTest::RemoveTree(std::shared_ptr<Tree> tree){
		_created_trees.remove(tree);
		_tree_timer->DetachFromSeconds(tree.get());
	}
}