#include "EmptyControlledActor.h"
//#include <SFML/Window.hpp>
namespace Core::Object {
	EmptyControlledActor::EmptyControlledActor(WorldBase* world, const Settings::ActorSettings& actorsettings, const Settings::TextureSettings& texturesettings, const Settings::AnimationSettings& animationsettings, Controller::ControllerBase* controller) :ControlledActor(world, actorsettings, texturesettings, animationsettings, controller) {
		if (_collider)
			_collider->setFillColor(sf::Color::Magenta);
	}

	void EmptyControlledActor::Tick(float deltatime) {
		ControlledActor::Tick(deltatime);
	}

	void EmptyControlledActor::Move(const sf::Vector2f& velocity) {
		ControlledActor::Move(velocity);
	}

	void EmptyControlledActor::Draw(sf::RenderWindow& window) {
		ControlledActor::Draw(window);
	}

	void EmptyControlledActor::Init() {
		SetTickFlag(_actor_settings.tick);
	}
}