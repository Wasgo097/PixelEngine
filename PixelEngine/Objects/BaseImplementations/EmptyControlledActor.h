#pragma once
#include "Objects/ControlledActor.h"
namespace Core {
	class EmptyControlledActor:public ControlledActor {
	public:
		EmptyControlledActor(WorldBase* world, const Settings::ActorSettings& actorsettings, const Settings::TextureSettings& texturesettings, const Settings::AnimationSettings& animationsettings, Controller::ControllerBase* controller);
		virtual ~EmptyControlledActor() = default;
	public:
		virtual void Tick(float deltatime);
		virtual void Move(const sf::Vector2f & velocity);
		virtual void Draw(sf::RenderWindow& window);
	};
}
