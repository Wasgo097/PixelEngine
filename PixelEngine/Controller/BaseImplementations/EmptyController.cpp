#include "EmptyController.h"
#include "Utility/CommonHeaders.h"
#include "Objects/BaseImplementations/EmptyControlledActor.h"
#include "Core/WorldBase.h"
namespace Controller {
	EmptyController::EmptyController(Core::WorldBase* world) :ControllerBase(world){
	}
	void EmptyController::SetMainCharacterInputBindings() {
		Controller::Key key;
		key._inputtype = Controller::InputType::MouseInput;
		key._eventtype = sf::Event::MouseButtonPressed;
		key._mousebutton = sf::Mouse::Left;
		_actions[key] = [](std::shared_ptr<Core::ControlledActor> _actor) {
			std::cout << "Left Button Pressed";
		};
		key._inputtype = Controller::InputType::KeyboardInput;
		key._eventtype = sf::Event::KeyPressed;
		key._keyboardbutton = sf::Keyboard::W;
		_actions[key] = [](std::shared_ptr<Core::ControlledActor> _actor) {
			std::cout << "W Pressed";
		};
		key._inputtype = Controller::InputType::KeyboardInput;
		key._eventtype = sf::Event::KeyPressed;
		key._keyboardbutton = sf::Keyboard::S;
		_actions[key] = [](std::shared_ptr<Core::ControlledActor> _actor) {
			std::cout << "S Pressed";
		};
		key._inputtype = Controller::InputType::KeyboardInput;
		key._eventtype = sf::Event::KeyPressed;
		key._keyboardbutton = sf::Keyboard::A;
		_actions[key] = [](std::shared_ptr<Core::ControlledActor> _actor) {
			std::cout << "A Pressed";
		};
		key._inputtype = Controller::InputType::KeyboardInput;
		key._eventtype = sf::Event::KeyPressed;
		key._keyboardbutton = sf::Keyboard::D;
		_actions[key] = [](std::shared_ptr<Core::ControlledActor> _actor) {
			std::cout << "D Pressed";
		};
	}

	void EmptyController::SetMainCharacter() {
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