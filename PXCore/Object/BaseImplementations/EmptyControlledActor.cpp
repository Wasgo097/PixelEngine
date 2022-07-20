#include "EmptyControlledActor.h"
namespace Core::Object {
	EmptyControlledActor::EmptyControlledActor(World::WorldBase* world, const Settings::ActorSettings& actorsettings, const Settings::TextureSettings& texturesettings, const Settings::AnimationSettings& animationsettings, Controller::ControllerBase* controller) :ControlledActor(world, actorsettings, texturesettings, animationsettings, controller) {
		if (auto collider=GetTComponent<Components::Collider>();collider)
			collider->GetCollider().setFillColor(sf::Color::Magenta);
	}
}