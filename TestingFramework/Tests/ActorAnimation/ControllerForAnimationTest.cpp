#include "ControllerForAnimationTest.h"
#include "Utility/CommonHeaders.h"
#include "Objects/BaseImplementations/EmptyControlledActor.h"
#include "Factory/SettingsFactory.h"
namespace Test {
	ControllerForAnimationTest::ControllerForAnimationTest(Core::WorldBase* world) :ControllerBase(world) {
	}

	void ControllerForAnimationTest::InitMainCharacterInputBindings() {
		Controller::Key key;
		std::cout << "Init keybinding\n";
		key.input_type = Controller::InputType::MouseInput;
		key.event_type = sf::Event::MouseButtonPressed;
		key.mouse_button = sf::Mouse::Left;
		_actions[key] = [](std::shared_ptr<Core::ControlledActor> Actor) {
			std::cout << "Left Button Pressed\n";
		};
		key.input_type = Controller::InputType::KeyboardInput;
		key.event_type = sf::Event::KeyPressed;
		key.keyboard_button = sf::Keyboard::W;
		_actions[key] = [](std::shared_ptr<Core::ControlledActor> Actor) {
			//std::cout << "W Pressed\n";
			Actor->Move(sf::Vector2f(0, -2.0));
		};
		key.input_type = Controller::InputType::KeyboardInput;
		key.event_type = sf::Event::KeyPressed;
		key.keyboard_button = sf::Keyboard::S;
		_actions[key] = [](std::shared_ptr<Core::ControlledActor> Actor) {
			//std::cout << "S Pressed\n";
			Actor->Move(sf::Vector2f(0, 2.0));
		};
		key.input_type = Controller::InputType::KeyboardInput;
		key.event_type = sf::Event::KeyPressed;
		key.keyboard_button = sf::Keyboard::A;
		_actions[key] = [](std::shared_ptr<Core::ControlledActor> Actor) {
			//std::cout << "A Pressed\n";
			Actor->Move(sf::Vector2f(-2.0, 0));
		};
		key.input_type = Controller::InputType::KeyboardInput;
		key.event_type = sf::Event::KeyPressed;
		key.keyboard_button = sf::Keyboard::D;
		_actions[key] = [](std::shared_ptr<Core::ControlledActor> Actor) {
			//std::cout << "D Pressed\n";
			Actor->Move(sf::Vector2f(2.0, 0));
		};
	}

	void ControllerForAnimationTest::InitMainCharacter() {
		auto ActorSettings = CREATE_SETTINGS(Settings::ActorSettings, "Cfg\\MainActorSettings.json");
		auto TextureSettings = CREATE_SETTINGS(Settings::TextureSettings, "Cfg\\MainTextureSettings.json");
		auto AnimationSettings = CREATE_SETTINGS(Settings::AnimationSettings, "Cfg\\MainAnimationSettings.json");
		_main_character = std::make_shared<Core::EmptyControlledActor>(_world, ActorSettings, TextureSettings, AnimationSettings, this);
	}

}