#include "WorldForForestTest.h"
#include "PXFactory/SettingsFactory.h"
#include "PXCore/World/Components/FpsCounter.h"
#include "PXCore/World/Components/MainActorPositionIndicator.h"
#include "ControllerForForestTest.h"
#include "Actors/Tree.h"
#include "PXCore/Engine.h"
using namespace Core;
namespace Test {
	WorldForForestTest::WorldForForestTest(const Settings::WorldSettings& world_settings, Core::Engine* parent) :WorldBaseGUI(world_settings, parent), _tree_timer{ 0.5f } {
		_main_controller = std::make_unique<Test::ControllerForForestTest>(this, world_settings);
		_map = Core::World::Map();
		if (!_map->texture.loadFromFile("Resource\\TestMap.jpg"))
			throw std::invalid_argument("Wrong main map path");
		_map->map.setTexture(&_map->texture);
		_map->map.setSize(sf::Vector2f(_map->texture.getSize()));
		_map->map.setOrigin(_map->map.getSize() / 2.0f);
		_map->map.setPosition(.0f, .0f);
	}
	void WorldForForestTest::CheckQuit() {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			_quit = true;
	}
	void WorldForForestTest::Draw(sf::RenderWindow& window) {
		WorldBaseGUI::Draw(window);
		DEBUGDrawDeadZone(window);
	}
	void WorldForForestTest::DEBUGDrawDeadZone(sf::RenderWindow& window)const {
		sf::Vertex line1[] = {
			sf::Vertex(sf::Vector2f(_world_settings.deadzone_x, _world_settings.deadzone_y)),
			sf::Vertex(sf::Vector2f(_world_settings.deadzone_x, -_world_settings.deadzone_y)),
		};
		sf::Vertex line2[] = {
			sf::Vertex(sf::Vector2f(_world_settings.deadzone_x, _world_settings.deadzone_y)),
			sf::Vertex(sf::Vector2f(-_world_settings.deadzone_x, _world_settings.deadzone_y)),
		};
		sf::Vertex line3[] = {
			sf::Vertex(sf::Vector2f(-_world_settings.deadzone_x, -_world_settings.deadzone_y)),
			sf::Vertex(sf::Vector2f(-_world_settings.deadzone_x, _world_settings.deadzone_y)),
		};
		sf::Vertex line4[] = {
			sf::Vertex(sf::Vector2f(-_world_settings.deadzone_x, -_world_settings.deadzone_y)),
			sf::Vertex(sf::Vector2f(_world_settings.deadzone_x, -_world_settings.deadzone_y)),
		};
		window.draw(line1, 2, sf::Lines);
		window.draw(line2, 2, sf::Lines);
		window.draw(line3, 2, sf::Lines);
		window.draw(line4, 2, sf::Lines);
	}
	void WorldForForestTest::InitWorld() {
		WorldBaseGUI::InitWorld();
		const float windowHeight = _gui.getView().getRect().height;
		_gui.setTextSize(static_cast<unsigned int>(0.03f * windowHeight));
		OnSpawnActor = [this](std::shared_ptr<Core::Object::Actor>) {
			if (auto actors_counter = GetActorsCounter(); actors_counter)
				actors_counter->SetCountOfActors(_actor_manager->GetCountOfActors());
		};
		OnActorsRemoved = [this]() {
			if (auto actors_counter = GetActorsCounter(); actors_counter)
				actors_counter->SetCountOfActors(_actor_manager->GetCountOfActors());
		};
		auto tree_settings = CREATE_SETTINGS(Settings::ActorSettings, "Cfg\\TreeActorSettings.json");
		auto tree_texture = CREATE_SETTINGS(Settings::TextureSettings, "Cfg\\TreeTextureSettings.json");
		SpawnActor<Tree>(tree_settings, tree_texture);
		tree_settings.position.x += 100.0f;
		SpawnActor<Tree>(tree_settings, tree_texture);
		auto world_music = std::make_unique<sf::Music>();
		world_music->openFromFile("Resource\\Music_and_sound_effect\\1forest.ogg");
		_parent->PushNewMusicToPlay(std::move(world_music));
	}
	void WorldForForestTest::AddTree(std::shared_ptr<Tree> tree) {
		_created_trees.push_back(tree);
		_tree_timer.AttachToSeconds(tree.get());
	}
	void WorldForForestTest::RemoveTree(std::shared_ptr<Tree> tree) {
		_created_trees.remove(tree);
		_tree_timer.DetachFromSeconds(tree.get());
	}
	void WorldForForestTest::CreateWorldBaseGUIComponents() {
		tgui::Theme theme{ "Resource\\GUI\\themes\\TransparentGrey.txt" };
		if (auto parser = _parent->GetParser(); parser and parser->get().GetValue<bool>("-fpscounter"))
			_gui_world_components.emplace_back(std::make_shared<Core::World::Component::FpsCounter>(this, &_gui, theme));
		//_gui_world_components.emplace_back(std::make_shared<Core::World::Component::ActorsCounter>(this, &_gui, theme));
		_gui_world_components.emplace_back(std::make_shared<Core::World::Component::MainActorPositionIndicator>(this, &_gui, theme, _main_controller->GetMainCharacter()));
	}
	void WorldForForestTest::InitGuiSettup() {
		WorldBaseGUI::InitGuiSettup();
		DrawWorldBaseGUIComponents();
	}
	std::shared_ptr<Core::World::Component::ActorsCounter> WorldForForestTest::GetActorsCounter() const {
		return GetTGuiComponent<Core::World::Component::ActorsCounter>();
	}
}