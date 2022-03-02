#pragma once
#include "AnimatedActor.h"
#include "Controller/ControllerStructs.h"
#include <functional>
namespace Controller {
	class ControllerBase;
}
namespace Core{
	class ControlledActor:public AnimatedActor{
	public:
		ControlledActor(WorldBase* world, const Settings::ActorSettings& actorsettings, const Settings::TextureSettings& texturesettings, const Settings::AnimationSettings& animationsettings,Controller::ControllerBase * controllerptr);
		ControlledActor(const ControlledActor&) = delete;
		ControlledActor(ControlledActor&&) = delete;
		ControlledActor& operator=(const ControlledActor&) = delete;
		ControlledActor& operator=(ControlledActor&&) = delete;
		virtual ~ControlledActor() = default;
	public:
		virtual void Tick(float deltatime)override;
		virtual void Move(const sf::Vector2f& velocity)override;
		virtual void ConstPush(const sf::Vector2f& constvelocity)override;
		virtual void Draw(sf::RenderWindow & window)override;
	public:
		virtual void Init()override;
		virtual void OnLoad()override{}
		virtual void OnSpawn()override{}
		virtual void OnDelete()override{}
		virtual std::string ToString()const override;
	public:
		bool ServiceInput(sf::Event e);
		virtual void LoadActions();
	protected:
		bool TestEvent(const Controller::Key& k, sf::Event e);
		void DoAction(const Controller::Key& key);
	protected:
		std::map<Controller::Key, std::function<void()>> _actions;
		Controller::ControllerBase* _controller = nullptr;
	};
}