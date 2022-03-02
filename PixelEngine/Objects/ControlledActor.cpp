#include "Utility/CommonHeaders.h"
#include "ControlledActor.h"
#include "Controller/ControllerBase.h"
namespace Core{
	ControlledActor::ControlledActor(WorldBase* world, const Settings::ActorSettings& actorsettings, const Settings::TextureSettings& texturesettings, const Settings::AnimationSettings& animationsettings, Controller::ControllerBase* controllerptr)
	:AnimatedActor(world, actorsettings, texturesettings,animationsettings),_controller(controllerptr){
	}
	void ControlledActor::Tick(float deltatime){
		AnimatedActor::Tick(deltatime);
	}
	void ControlledActor::Move(const sf::Vector2f & velocity){
		AnimatedActor::Move(velocity);
	}
	void ControlledActor::ConstPush(const sf::Vector2f & constvelocity){
		AnimatedActor::ConstPush(constvelocity);
	}
	void ControlledActor::Draw(sf::RenderWindow & window){
		AnimatedActor::Draw(window);
	}
	void ControlledActor::Init() {
		LoadActions();
	}
	std::string ControlledActor::ToString() const{ 
		return "Default ControlledActor ToString"; 
	}
	bool ControlledActor::ServiceInput(sf::Event e){
		for(const auto &[Key, Value] : _actions){
			if(TestEvent(Key, e)){
				DoAction(Key);
				return true;
			}
		}
		return false;
	}
	void ControlledActor::LoadActions(){
		Controller::Key key;
		key._inputtype = Controller::InputType::MouseInput;
		key._eventtype = sf::Event::MouseButtonPressed;
		key._mousebutton = sf::Mouse::Left;
		_actions[key] = [] (){
			std::cout << "Left Button Pressed";
		};
		key._inputtype = Controller::InputType::KeyboardInput;
		key._eventtype = sf::Event::KeyPressed;
		key._keyboardbutton = sf::Keyboard::W;
		_actions[key] = [] (){
			std::cout << "W Pressed";
		};
		key._inputtype = Controller::InputType::KeyboardInput;
		key._eventtype = sf::Event::KeyPressed;
		key._keyboardbutton = sf::Keyboard::S;
		_actions[key] = [] (){
			std::cout << "S Pressed";
		};
		key._inputtype = Controller::InputType::KeyboardInput;
		key._eventtype = sf::Event::KeyPressed;
		key._keyboardbutton = sf::Keyboard::A;
		_actions[key] = [] (){
			std::cout << "A Pressed";
		};
		key._inputtype = Controller::InputType::KeyboardInput;
		key._eventtype = sf::Event::KeyPressed;
		key._keyboardbutton = sf::Keyboard::D;
		_actions[key] = [] (){
			std::cout << "D Pressed";
		};
	}
	bool ControlledActor::TestEvent(const Controller::Key & k, sf::Event e){
		// Mouse event
		if(k._inputtype == Controller::InputType::MouseInput &&
			k._eventtype == e.type &&
			k._mousebutton == e.mouseButton.button){
			return true;
		}
		// Keyboard event
		if(k._inputtype == Controller::InputType::KeyboardInput &&
			k._eventtype == e.type &&
			k._keyboardbutton == e.key.code){
			return true;
		}
		//todo service joystick input here
		return false;
	}
	void ControlledActor::DoAction(const Controller::Key & key){
		_actions[key]();
	}
}