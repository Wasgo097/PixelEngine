#pragma once
#include "Actor.h"
#include "Components/Animation.h"
#include "PXSettings/AnimationSettings.h"
#include "PXUtilities/Enums/AnimationEnums.h"
namespace Core::Object{
	class AnimatedActor :public Actor{
	public:
		AnimatedActor(World::WorldBase* world, const Settings::ActorSettings& actor_settings, const Settings::TextureSettings& texture_settings, const Settings::AnimationSettings& animation_settings);
		AnimatedActor(const AnimatedActor&) = delete;
		AnimatedActor&operator=(const AnimatedActor&) = delete;
		AnimatedActor(AnimatedActor&&) = delete;
		AnimatedActor&operator=(AnimatedActor&&) = delete;
		virtual ~AnimatedActor() = default;

		virtual void Tick(float delta_time)override;
		virtual void Move(const sf::Vector2f& velocity)override;
		virtual std::string ToString()const override;
	protected:
		void CheckAnimatedRow();
		Settings::AnimationSettings _animation_settings;
		std::map<AnimationEnums::Direction, int> _direction_row;
		int _animated_row = 0;
	};
}