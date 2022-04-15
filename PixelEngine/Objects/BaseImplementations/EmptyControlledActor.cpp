#include "EmptyControlledActor.h"
#include <SFML/Window.hpp>
#include <iostream>
Core::EmptyControlledActor::EmptyControlledActor(WorldBase* world, const Settings::ActorSettings& actorsettings, const Settings::TextureSettings& texturesettings, const Settings::AnimationSettings& animationsettings, Controller::ControllerBase* controller):ControlledActor(world,actorsettings,texturesettings,animationsettings,controller)
{
	if (_collider)
		_collider->setFillColor(sf::Color::Magenta);
}

void Core::EmptyControlledActor::Tick(float deltatime){
	ControlledActor::Tick(deltatime);
}

void Core::EmptyControlledActor::Move(const sf::Vector2f& velocity){
	ControlledActor::Move(velocity);
}

void Core::EmptyControlledActor::Draw(sf::RenderWindow& window){
	ControlledActor::Draw(window);
	if (_collider)
		window.draw(*_collider);
}

void Core::EmptyControlledActor::Init()
{
	SetTickFlag(true);
}
