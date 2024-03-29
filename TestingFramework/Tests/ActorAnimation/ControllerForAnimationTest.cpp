#include "ControllerForAnimationTest.h"
#include "PXCore/Object/BaseImplementations/EmptyControlledActor.h"
#include "PXFactory/SettingsFactory.h"
namespace Test {
	ControllerForAnimationTest::ControllerForAnimationTest(Core::World::WorldBase* world) :ControllerBase(world) {
	}

	void ControllerForAnimationTest::InitMainCharacterInputBindings() {
		Core::Controller::Key key;
		key.input_type = Core::Controller::InputType::MouseInput;
		key.event_type = sf::Event::MouseButtonPressed;
		key.mouse_button = sf::Mouse::Left;
		_actions[key] = [](std::shared_ptr<Core::Object::ControlledActor> actor) {
			std::cout << "Left Button Pressed\n";
		};
		key.input_type = Core::Controller::InputType::KeyboardInput;
		key.event_type = sf::Event::KeyPressed;
		key.keyboard_button = sf::Keyboard::W;
		_actions[key] = [](std::shared_ptr<Core::Object::ControlledActor> actor) {
			actor->Move(sf::Vector2f(0, -2.0));
		};
		key.keyboard_button = sf::Keyboard::S;
		_actions[key] = [](std::shared_ptr<Core::Object::ControlledActor> actor) {
			actor->Move(sf::Vector2f(0, 2.0));
		};
		key.keyboard_button = sf::Keyboard::A;
		_actions[key] = [](std::shared_ptr<Core::Object::ControlledActor> actor) {
			actor->Move(sf::Vector2f(-2.0, 0));
		};
		key.keyboard_button = sf::Keyboard::D;
		_actions[key] = [](std::shared_ptr<Core::Object::ControlledActor> actor) {
			actor->Move(sf::Vector2f(2.0, 0));
		};
	}

	void ControllerForAnimationTest::InitMainCharacter() {
		auto actor_settings = CREATE_SETTINGS(Settings::ActorSettings, "Cfg\\MainActorSettings.json");
		auto texture_settings = CREATE_SETTINGS(Settings::TextureSettings, "Cfg\\MainTextureSettings.json");
		auto animation_settings = CREATE_SETTINGS(Settings::AnimationSettings, "Cfg\\MainAnimationSettings.json");
		_main_character = std::make_shared<Core::Object::EmptyControlledActor>(_world_parent, actor_settings, texture_settings, animation_settings, this);
	}

}