#include "ControllerForForestTest.h"
#include "Actors/ForestMainCharacter.h"
#include "PXFactory/SettingsFactory.h"
namespace Test {
	ControllerForForestTest::ControllerForForestTest(Core::World::WorldBase* world) :ControllerBase(world) {
	}

	void ControllerForForestTest::InitMainCharacterInputBindings() {
		Core::Controller::Key key;
		std::cout << "Init keybinding\n";
		key.input_type = Core::Controller::InputType::MouseInput;
		key.event_type = sf::Event::MouseButtonPressed;
		key.mouse_button = sf::Mouse::Left;
		key.repeatable = false;
		_actions[key] = [](std::shared_ptr<Core::Object::ControlledActor> actor) {
			std::cout << "Left Button Clicked\n";
			if (auto ptr = std::dynamic_pointer_cast<ForestMainCharacter>(actor); ptr) {
				ptr->CreateNewTree();
			}
		};
		key.repeatable = true;
		key.mouse_button = sf::Mouse::Right;
		_actions[key] = [](std::shared_ptr<Core::Object::ControlledActor> actor) {
			std::cout << "Right Button Pressed\n";
			if (auto ptr = std::dynamic_pointer_cast<ForestMainCharacter>(actor); ptr)
				ptr->EraseTree();
		};
		key.input_type = Core::Controller::InputType::KeyboardInput;
		key.event_type = sf::Event::KeyPressed;
		key.keyboard_button = sf::Keyboard::W;
		_actions[key] = [](std::shared_ptr<Core::Object::ControlledActor> actor) {
			actor->Move(sf::Vector2f(0, -1.0));
		};
		key.keyboard_button = sf::Keyboard::S;
		_actions[key] = [](std::shared_ptr<Core::Object::ControlledActor> actor) {
			actor->Move(sf::Vector2f(0, 1.0));
		};
		key.keyboard_button = sf::Keyboard::A;
		_actions[key] = [](std::shared_ptr<Core::Object::ControlledActor> actor) {
			actor->Move(sf::Vector2f(-1.0, 0));
		};
		key.keyboard_button = sf::Keyboard::D;
		_actions[key] = [](std::shared_ptr<Core::Object::ControlledActor> actor) {
			actor->Move(sf::Vector2f(1.0, 0));
		};
	}

	void ControllerForForestTest::InitMainCharacter() {
		auto actor_settings = CREATE_SETTINGS(Settings::ActorSettings, "Cfg\\MainActorSettings.json");
		auto texture_settings = CREATE_SETTINGS(Settings::TextureSettings, "Cfg\\MainTextureSettings.json");
		auto animation_settings = CREATE_SETTINGS(Settings::AnimationSettings, "Cfg\\MainAnimationSettings.json");
		_main_character = std::make_shared<ForestMainCharacter>(_world_parent, actor_settings, texture_settings, animation_settings, this);
	}

}