#include "EmptyControlledActor.h"
namespace Core::Object {
	EmptyControlledActor::EmptyControlledActor(World::WorldBase* world, const Settings::ActorSettings& actorsettings, const Settings::TextureSettings& texturesettings, const Settings::AnimationSettings& animationsettings, Controller::ControllerBase* controller) :ControlledActor(world, actorsettings, texturesettings, animationsettings, controller) {
		if (_collider)
			_collider->setFillColor(sf::Color::Magenta);
	}

	void EmptyControlledActor::Init() {
		SetTickFlag(_actor_settings.tick);
	}
}