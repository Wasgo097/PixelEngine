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
		key._inputtype = Controller::InputType::MouseInput;
		key._eventtype = sf::Event::MouseButtonPressed;
		key._mousebutton = sf::Mouse::Left;
		_actions[key] = [](std::shared_ptr<Core::ControlledActor> Actor) {
			std::cout << "Left Button Pressed\n";
		};
		key._inputtype = Controller::InputType::KeyboardInput;
		key._eventtype = sf::Event::KeyPressed;
		key._keyboardbutton = sf::Keyboard::W;
		_actions[key] = [](std::shared_ptr<Core::ControlledActor> Actor) {
			//std::cout << "W Pressed\n";
			Actor->Move(sf::Vector2f(0, -1.0));
		};
		key._inputtype = Controller::InputType::KeyboardInput;
		key._eventtype = sf::Event::KeyPressed;
		key._keyboardbutton = sf::Keyboard::S;
		_actions[key] = [](std::shared_ptr<Core::ControlledActor> Actor) {
			//std::cout << "S Pressed\n";
			Actor->Move(sf::Vector2f(0, 1.0));
		};
		key._inputtype = Controller::InputType::KeyboardInput;
		key._eventtype = sf::Event::KeyPressed;
		key._keyboardbutton = sf::Keyboard::A;
		_actions[key] = [](std::shared_ptr<Core::ControlledActor> Actor) {
			//std::cout << "A Pressed\n";
			Actor->Move(sf::Vector2f(-1.0, 0));
		};
		key._inputtype = Controller::InputType::KeyboardInput;
		key._eventtype = sf::Event::KeyPressed;
		key._keyboardbutton = sf::Keyboard::D;
		_actions[key] = [](std::shared_ptr<Core::ControlledActor> Actor) {
			//std::cout << "D Pressed\n";
			Actor->Move(sf::Vector2f(1.0, 0));
		};
	}

	void ControllerForAnimationTest::InitMainCharacter() {
		auto ActorSettings = CREATE_SETTINGS(Settings::ActorSettings, "Cfg\\MainActorSettings.json");
		auto TextureSettings = CREATE_SETTINGS(Settings::TextureSettings, "Cfg\\MainTextureSettings.json");
		auto AnimationSettings = CREATE_SETTINGS(Settings::AnimationSettings, "Cfg\\MainAnimationSettings.json");
		_maincharacter = std::make_shared<Core::EmptyControlledActor>(_world, ActorSettings, TextureSettings, AnimationSettings, this);
	}

}