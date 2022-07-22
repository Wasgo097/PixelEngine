#pragma once
#include <stack>
#include <concepts>
#include <SFML/Graphics/RenderWindow.hpp>
#include "PXCore/Object/Actor.h"
#include "PXCore/Object/AnimatedActor.h"
#include "PXCore/Object/ControlledActor.h"
#include "PXCore/ActorsManager.h"
#include "PXSettings/WorldSettings.h"
namespace Core {
	class Engine;
}
namespace Core::World {
	class WorldBase {
	public:
		WorldBase(const Settings::WorldSettings& world_settings = Settings::WorldSettings(), Engine* parent = nullptr);
		virtual ~WorldBase() = default;

		template<typename type_to_create, typename ...Argv>
			requires std::derived_from<type_to_create, Core::Object::Actor>
		std::shared_ptr<type_to_create> SpawnActor(const Settings::ActorSettings& actor_settings, const Settings::TextureSettings& texture_settings, Argv && ...argv) {
			std::shared_ptr<type_to_create> result;
			type_to_create* ptr = new type_to_create(this, actor_settings, texture_settings, std::forward<Argv>(argv)...);
			result.reset(ptr);
			ptr = nullptr;
			_actor_manager->RegistrNewActor(result);
			return result;
		}
		template<typename type_to_create, typename ...Argv>
			requires std::derived_from<type_to_create, Core::Object::Actor>
		std::shared_ptr<type_to_create> SpawnConstActor(const Settings::ActorSettings& actor_settings, const Settings::TextureSettings& texture_settings, Argv && ...argv) {
			std::shared_ptr<type_to_create> result;
			type_to_create* ptr = new type_to_create(this, actor_settings, texture_settings, std::forward<Argv>(argv)...);
			result.reset(ptr);
			ptr = nullptr;
			_actor_manager->RegisterConstActor(result);
			return result;
		}
		template<typename type_to_create, typename ...Argv>
			requires std::derived_from<type_to_create, Core::Object::AnimatedActor>
		std::shared_ptr<type_to_create> SpawnAnimatedActor(const Settings::ActorSettings& actor_settings, const Settings::TextureSettings& texture_settings, const Settings::AnimationSettings& animation_settings, Argv && ...argv) {
			std::shared_ptr<type_to_create> result;
			type_to_create* ptr = new type_to_create(this, actor_settings, texture_settings, animation_settings, std::forward<Argv>(argv)...);
			result.reset(ptr);
			ptr = nullptr;
			_actor_manager->RegistrNewActor(result);
			return result;
		}
		virtual void Draw(sf::RenderWindow& window);
		virtual void Update(float delta);
		void SetParent(Engine* parent);
		bool Quit()const;
		bool Initialized()const;
		virtual void ServiceInput(const Core::Controller::Key& key);
		virtual void ServiceGUIInput(const sf::Event& action) {};
		virtual void InitWorld();
		virtual void EndWorld();
		virtual void CheckQuit() = 0;
	protected:
		Engine* _parent = nullptr;
		Settings::WorldSettings _world_settings;
		std::unique_ptr<ActorsManager> _actor_manager;
		std::unique_ptr<Controller::ControllerBase> _main_controller;
		bool _quit = false;
		bool _initialized = false;
	};
}
