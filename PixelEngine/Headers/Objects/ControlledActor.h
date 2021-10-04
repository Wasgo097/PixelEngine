#pragma once
#include "AnimatedActor.h"
#include "Controller/ControllerStructs.h"
namespace Core{
	class ControlledActor:public AnimatedActor{
		ControlledActor(World* world, const Settings::ActorSettings & settings, const Settings::AnimationSettings& animationsettings);
		ControlledActor(const ControlledActor&) = delete;
		ControlledActor(ControlledActor&&) = delete;
		ControlledActor& operator=(const ControlledActor&) = delete;
		ControlledActor& operator=(ControlledActor&&) = delete;
		virtual ~ControlledActor() = default;
	public:
		virtual void Tick(float deltatime);
		virtual void Move(const sf::Vector2f& velocity);
		virtual void Push(const sf::Vector2f& constvelocity);
		virtual void Draw(sf::RenderWindow & window);
		virtual std::string ToString()const override;
	protected:
		//Settings::ControllerSettings _controlsettings;
		//std::map<Controller::Key, std::function<void()>> _actions;
	};
}