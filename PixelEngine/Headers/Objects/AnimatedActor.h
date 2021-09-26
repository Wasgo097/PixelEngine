#pragma once
#include "Actor.h"
#include "Extensions/Animation.h"
namespace Core{
	class AnimatedActor :public Actor{
	public:
		AnimatedActor(World* world, const Settings::ActorSettings & settings, const Settings::AnimationTextureSettings& animatedtexture) :Actor(world, settings), _animationsettings(animatedtexture){

		}
	protected:
		Settings::AnimationTextureSettings _animationsettings;
		std::unique_ptr<Core::Animation::Animation> _animation;
	};
}