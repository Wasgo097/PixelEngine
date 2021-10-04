#pragma once
#include "Actor.h"
#include "Extensions/Animation.h"
#include "Settings/AnimationSettings.h"
namespace Core{
	class AnimatedActor :public Actor{
	public:
		AnimatedActor(World* world, const Settings::ActorSettings & settings, const Settings::AnimationSettings& animationsettings);
		AnimatedActor(const AnimatedActor&) = delete;
		AnimatedActor&operator=(const AnimatedActor&) = delete;
		AnimatedActor(AnimatedActor&&) = delete;
		AnimatedActor&operator=(AnimatedActor&&) = delete;
		virtual ~AnimatedActor() = default;
	public:
		virtual void Tick(float deltatime);
		virtual void Move(const sf::Vector2f& velocity);
		virtual void Push(const sf::Vector2f& constvelocity);
		virtual void Draw(sf::RenderWindow & window);
		virtual std::string ToString()const override;
	protected:
		Settings::AnimationSettings _animationsettings;
		std::unique_ptr<Animation::Animation> _animation;
		std::map<Animation::Direction, int>& _directiontorowref;
		int _animatedrow = 0;
	};
}