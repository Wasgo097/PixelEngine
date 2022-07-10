#include "ControllerForForestTest.h"
#include "PXCore/Object/BaseImplementations/EmptyControlledActor.h"
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
		_actions[key] = [](std::shared_ptr<Core::Object::ControlledActor> Actor) {
			std::cout << "Left Button Pressed\n";
		};
		key.input_type = Core::Controller::InputType::KeyboardInput;
		key.event_type = sf::Event::KeyPressed;
		key.keyboard_button = sf::Keyboard::W;
		_actions[key] = [](std::shared_ptr<Core::Object::ControlledActor> Actor) {
			Actor->Move(sf::Vector2f(0, -1.0));
		};
		key.input_type = Core::Controller::InputType::KeyboardInput;
		key.event_type = sf::Event::KeyPressed;
		key.keyboard_button = sf::Keyboard::S;
		_actions[key] = [](std::shared_ptr<Core::Object::ControlledActor> Actor) {
			Actor->Move(sf::Vector2f(0, 1.0));
		};
		key.input_type = Core::Controller::InputType::KeyboardInput;
		key.event_type = sf::Event::KeyPressed;
		key.keyboard_button = sf::Keyboard::A;
		_actions[key] = [](std::shared_ptr<Core::Object::ControlledActor> Actor) {
			Actor->Move(sf::Vector2f(-1.0, 0));
		};
		key.input_type = Core::Controller::InputType::KeyboardInput;
		key.event_type = sf::Event::KeyPressed;
		key.keyboard_button = sf::Keyboard::D;
		_actions[key] = [](std::shared_ptr<Core::Object::ControlledActor> Actor) {
			Actor->Move(sf::Vector2f(1.0, 0));
		};
	}

	void ControllerForForestTest::InitMainCharacter() {
		auto ActorSettings = CREATE_SETTINGS(Settings::ActorSettings, "Cfg\\MainActorSettings.json");
		auto TextureSettings = CREATE_SETTINGS(Settings::TextureSettings, "Cfg\\MainTextureSettings.json");
		auto AnimationSettings = CREATE_SETTINGS(Settings::AnimationSettings, "Cfg\\MainAnimationSettings.json");
		_main_character = std::make_shared<Core::Object::EmptyControlledActor>(_world_parent, ActorSettings, TextureSettings, AnimationSettings, this);
	}

}