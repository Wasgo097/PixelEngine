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
	std::string ControlledActor::ToString() const{ 
		return "Default ControlledActor ToString"; 
	}
}