#include "EmptyController.h"
#include <iostream>
#include "Object/BaseImplementations/EmptyControlledActor.h"
#include "PXSettings/ActorSettings.h"
#include "PXSettings/TextureSettings.h"
#include "PXSettings/AnimationSettings.h"
namespace Core::Controller {
	Controller::EmptyController::EmptyController(Core::World::WorldBase* world) :_world { world }
	{
	}
	void EmptyController::InitMainCharacterInputBindings() {
		Controller::Key key;
		std::cout << "Init Keybinding\n";
		key.input_type = Controller::InputType::MouseInput;
		key.event_type = sf::Event::MouseButtonPressed;
		key.mouse_button = sf::Mouse::Left;
		_actions[key] = [](std::shared_ptr<Core::Object::ControlledActor> Actor) {
			std::cout << "Left Button Pressed\n";
		};
		key.input_type = Controller::InputType::KeyboardInput;
		key.event_type = sf::Event::KeyPressed;
		key.keyboard_button = sf::Keyboard::W;
		_actions[key] = [](std::shared_ptr<Core::Object::ControlledActor> Actor) {
			//std::cout << "W Pressed\n";
			Actor->Move(sf::Vector2f(0, -10.0));
		};
		key.input_type = Controller::InputType::KeyboardInput;
		key.event_type = sf::Event::KeyPressed;
		key.keyboard_button = sf::Keyboard::S;
		_actions[key] = [](std::shared_ptr<Core::Object::ControlledActor> Actor) {
			//std::cout << "S Pressed\n";
			Actor->Move(sf::Vector2f(0, 10.0));
		};
		key.input_type = Controller::InputType::KeyboardInput;
		key.event_type = sf::Event::KeyPressed;
		key.keyboard_button = sf::Keyboard::A;
		_actions[key] = [](std::shared_ptr<Core::Object::ControlledActor> Actor) {
			//std::cout << "A Pressed\n";
			Actor->Move(sf::Vector2f(-10.0,0));
		};
		key.input_type = Controller::InputType::KeyboardInput;
		key.event_type = sf::Event::KeyPressed;
		key.keyboard_button = sf::Keyboard::D;
		_actions[key] = [](std::shared_ptr<Core::Object::ControlledActor> Actor) {
			//std::cout << "D Pressed\n";
			Actor->Move(sf::Vector2f(10.0, 0));
		};
	}

	void EmptyController::InitMainCharacter() {
		std::cout << "Init Main Character\n";
		Settings::ActorSettings actor_settings;
		actor_settings.collider_size = sf::Vector2f(20, 20);
		actor_settings.collision = ActorsEnums::CollisionType::Collision;
		actor_settings.position = sf::Vector2f(20,20);
		actor_settings.tick = true;
		actor_settings.type = ActorsEnums::ActorType::Dynamic;
		Settings::TextureSettings texture_settings;
		texture_settings.repeatable = false;
		texture_settings.smooth = true;
		texture_settings.texture_path = "";
		Settings::AnimationSettings animation_settings;
		_main_character = std::make_shared<Core::Object::EmptyControlledActor>(_world, actor_settings, texture_settings, animation_settings, this);
	}
}