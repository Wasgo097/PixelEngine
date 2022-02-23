#include "CommonHeaders.h"
#include "Objects/ControlledActor.h"
#define DefaultInput
namespace Core{
	ControlledActor::ControlledActor(World* world, const Settings::ActorSettings& actorsettings, const Settings::TextureSettings& texturesettings, const Settings::AnimationSettings& animationsettings)
	:AnimatedActor(world, actorsettings, texturesettings,animationsettings){
#ifdef DefaultInput
		LoadTestActions();
#endif // DefaultInput
	}
	void ControlledActor::Tick(float deltatime){
		AnimatedActor::Tick(deltatime);
	}
	void ControlledActor::Move(const sf::Vector2f & velocity){
		AnimatedActor::Move(velocity);
	}
	void ControlledActor::Push(const sf::Vector2f & constvelocity){
		AnimatedActor::Push(constvelocity);
	}
	void ControlledActor::Draw(sf::RenderWindow & window){
		AnimatedActor::Draw(window);
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
	void ControlledActor::LoadTestActions(){
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