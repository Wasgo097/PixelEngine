#include "EmptyController.h"
#include "Utility/CommonHeaders.h"
#include "Objects/BaseImplementations/EmptyControlledActor.h"
#include "Core/World/WorldBase.h"
namespace Controller {
	EmptyController::EmptyController(Core::WorldBase* world) :ControllerBase(world){
	}
	void EmptyController::InitMainCharacterInputBindings() {
		Controller::Key key;
		std::cout << "Init Keybinding\n";
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
			Actor->Move(sf::Vector2f(0, -10.0));
		};
		key._inputtype = Controller::InputType::KeyboardInput;
		key._eventtype = sf::Event::KeyPressed;
		key._keyboardbutton = sf::Keyboard::S;
		_actions[key] = [](std::shared_ptr<Core::ControlledActor> Actor) {
			//std::cout << "S Pressed\n";
			Actor->Move(sf::Vector2f(0, 10.0));
		};
		key._inputtype = Controller::InputType::KeyboardInput;
		key._eventtype = sf::Event::KeyPressed;
		key._keyboardbutton = sf::Keyboard::A;
		_actions[key] = [](std::shared_ptr<Core::ControlledActor> Actor) {
			//std::cout << "A Pressed\n";
			Actor->Move(sf::Vector2f(-10.0,0));
		};
		key._inputtype = Controller::InputType::KeyboardInput;
		key._eventtype = sf::Event::KeyPressed;
		key._keyboardbutton = sf::Keyboard::D;
		_actions[key] = [](std::shared_ptr<Core::ControlledActor> Actor) {
			//std::cout << "D Pressed\n";
			Actor->Move(sf::Vector2f(10.0, 0));
		};
	}

	void EmptyController::InitMainCharacter() {
		std::cout << "Init Main Character\n";
		Settings::ActorSettings actorsettings;
		actorsettings.ColliderSize = sf::Vector2f(20, 20);
		actorsettings.CollisionType = ActorsEnums::CollisionType::Collision;
		actorsettings.Position = sf::Vector2f(20,20);
		actorsettings.TickFlag = true;
		actorsettings.ActorType = ActorsEnums::ActorType::Dynamic;
		Settings::TextureSettings texturesettings;
		texturesettings._repeatable = false;
		texturesettings._smooth = true;
		texturesettings._texturepath = "";
		Settings::AnimationSettings animationsettings;
		_maincharacter = std::make_shared<Core::EmptyControlledActor>(_world, actorsettings, texturesettings, animationsettings, this);
	}
}