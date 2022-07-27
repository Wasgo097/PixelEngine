#include "Fireball.h"
namespace Test {
	Fireball::Fireball(Core::World::WorldBase* world, const Settings::ActorSettings& actor_settings, const Settings::TextureSettings& texture_settings, const Settings::AnimationSettings& animation_settings) :
		AnimatedActor(world, actor_settings, texture_settings, animation_settings) {
	}
	void Fireball::OnCollide(const Actor* other, std::optional<sf::Vector2f> diference) {
		Destroy();
	}
}