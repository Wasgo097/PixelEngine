#pragma once
#include "PXCore/Object/ControlledActor.h"
namespace Core::Object {
	class EmptyControlledActor:public ControlledActor {
	public:
		EmptyControlledActor(WorldBase* world, const Settings::ActorSettings& actorsettings, const Settings::TextureSettings& texturesettings, const Settings::AnimationSettings& animationsettings, Core::Controller::ControllerBase* controller);
	public:
		virtual void Tick(float deltatime)override;
		virtual void Move(const sf::Vector2f & velocity)override;
		virtual void Draw(sf::RenderWindow& window)override;
		virtual void Init()override;
	};
}
