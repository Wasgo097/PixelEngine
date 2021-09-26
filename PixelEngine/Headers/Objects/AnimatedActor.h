#pragma once
#include "Actor.h"
#include "Extensions/Animation.h"
namespace Core{
	class AnimatedActor :public Actor{
	public:
		AnimatedActor(World* world, const Settings::ActorSettings & settings, const Settings::AnimationTextureSettings& animatedtexture) :Actor(world, settings), _animationsettings(animatedtexture){
			sf::Vector2f temporigin(_animationsettings.GetRectSize().x, _animationsettings.GetRectSize().y);
			temporigin.x /= 2.0f;
			_sprite->setOrigin(temporigin);
			_sprite->setPosition(_settings.GetPosition());
		}
		AnimatedActor(const AnimatedActor&) = delete;
		AnimatedActor&operator=(const AnimatedActor&) = delete;
		AnimatedActor(AnimatedActor&&) = delete;
		AnimatedActor&operator=(AnimatedActor&&) = delete;
		virtual ~AnimatedActor() = default;
	public:
		virtual void Move(const sf::Vector2f& velocity);
		virtual void Draw(sf::RenderWindow & window);
	protected:
		Settings::AnimationTextureSettings _animationsettings;
		std::unique_ptr<Core::Animation::Animation> _animation;
	};
}