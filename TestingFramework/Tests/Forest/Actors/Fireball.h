#pragma once
#include "PXCore/Object/AnimatedActor.h"
namespace Test {
	class Fireball :public Core::Object::AnimatedActor {
	public:
		Fireball(Core::World::WorldBase* world, const Settings::ActorSettings& actor_settings, const Settings::TextureSettings& texture_settings, const Settings::AnimationSettings& animation_settings);
		virtual void OnCollide(const Actor* other, std::optional<sf::Vector2f> diference)override;
	};
}