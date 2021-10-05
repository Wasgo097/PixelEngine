#pragma once
#include "AnimatedActor.h"
#include "Controller/ControllerStructs.h"
#include <functional>
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
	public:
		bool ServiceInput(sf::Event e);
		void LoadTestActions();
	protected:
		bool TestEvent(const Controller::Key& k, sf::Event e);
		void DoAction(const Controller::Key& key);
	protected:
		std::map<Controller::Key, std::function<void()>> _actions;
	};
}