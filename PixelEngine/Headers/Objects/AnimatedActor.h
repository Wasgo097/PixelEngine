#pragma once
#include "Actor.h"
namespace Core{
	class AnimatedActor :public Actor{
	public:
		AnimatedActor(World* world, const Settings::ActorSettings & settings, const Settings::AnimatedTextureSettings& animatedtexture):Actor(world,settings),_animationsettings(animatedtexture){

		}
	protected:
		Settings::AnimatedTextureSettings _animationsettings;
	};
}