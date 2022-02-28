#pragma once
#include "Actor.h"
#include "Extensions/Animation.h"
#include "Settings/AnimationSettings.h"
#include "Enums/AnimationEnums.h"
namespace Core{
	class AnimatedActor :public Actor{
	public:
		AnimatedActor(World* world, const Settings::ActorSettings& actorsettings, const Settings::TextureSettings& texturesettings, const Settings::AnimationSettings& animationsettings);
		AnimatedActor(const AnimatedActor&) = delete;
		AnimatedActor&operator=(const AnimatedActor&) = delete;
		AnimatedActor(AnimatedActor&&) = delete;
		AnimatedActor&operator=(AnimatedActor&&) = delete;
		virtual ~AnimatedActor() = default;
	public:
		virtual void Tick(float deltatime)override;
		virtual void Move(const sf::Vector2f& velocity)override;
		virtual void ConstPush(const sf::Vector2f& constvelocity)override;
		virtual void Draw(sf::RenderWindow & window)override;
	public:
		virtual void Init()override{}
		virtual void OnLoad()override{}
		virtual void OnSpawn()override{}
		virtual void OnDelete()override{}
		virtual std::string ToString()const override;
	protected:
		Settings::AnimationSettings _animationsettings;
		std::unique_ptr<Animation::Animation> _animation;
		std::map<AnimationEnums::Direction, int>& _directiontorowref;
		int _animatedrow = 0;
	};
}