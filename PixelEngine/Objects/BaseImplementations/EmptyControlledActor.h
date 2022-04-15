#pragma once
#include "Objects/ControlledActor.h"
namespace Core {
	class EmptyControlledActor:public ControlledActor {
	public:
		EmptyControlledActor(WorldBase* world, const Settings::ActorSettings& actorsettings, const Settings::TextureSettings& texturesettings, const Settings::AnimationSettings& animationsettings, Controller::ControllerBase* controller);
	public:
		virtual void Tick(float deltatime)override;
		virtual void Move(const sf::Vector2f & velocity)override;
		virtual void Draw(sf::RenderWindow& window)override;
		virtual void Init()override;
	};
}
