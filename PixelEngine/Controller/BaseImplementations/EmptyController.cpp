#include "EmptyController.h"
#include "Utility/CommonHeaders.h"
#include "Objects/BaseImplementations/EmptyControlledActor.h"
#include "Core/World/WorldBase.h"
namespace Controller {
	EmptyController::EmptyController(Core::WorldBase* world) :ControllerBase(world){
	}
	void EmptyController::InitMainCharacterInputBindings() {
		Controller::Key key;
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
		Settings::ActorSettings actorsettings;
		actorsettings._collidersize = sf::Vector2f(20, 20);
		actorsettings._collision = ActorsEnums::CollisionType::Collision;
		actorsettings._position = sf::Vector2f(20, 20);
		actorsettings._tickflag = true;
		actorsettings._type = ActorsEnums::ActorType::Dynamic;
		Settings::TextureSettings texturesettings;
		texturesettings._repeatable = false;
		texturesettings._smooth = true;
		texturesettings._texturepath = "";
		Settings::AnimationSettings animationsettings;
		_maincharacter = std::make_shared<Core::EmptyControlledActor>(_world, actorsettings, texturesettings, animationsettings, this);
	}
}