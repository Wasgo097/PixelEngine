#pragma once
#include <stack>
#include <concepts>
#include <functional>
#include <SFML/Graphics/RenderWindow.hpp>
#include "PXCore/Object/Actor.h"
#include "PXCore/Object/AnimatedActor.h"
#include "PXCore/Object/ControlledActor.h"
#include "PXCore/ActorsManager.h"
#include "PXSettings/WorldSettings.h"
#include "Components/WorldBaseComponent.h"
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
			result.reset(new type_to_create(this, actor_settings, texture_settings, std::forward<Argv>(argv)...));
			_actor_manager->RegistrNewActor(result);
			result->OnSpawn();
			if (OnSpawnActor)
				OnSpawnActor(result);
			return result;
		}
		template<typename type_to_create, typename ...Argv>
			requires std::derived_from<type_to_create, Core::Object::Actor>
		std::shared_ptr<type_to_create> SpawnConstActor(const Settings::ActorSettings& actor_settings, const Settings::TextureSettings& texture_settings, Argv && ...argv) {
			std::shared_ptr<type_to_create> result;
			result.reset(new type_to_create(this, actor_settings, texture_settings, std::forward<Argv>(argv)...));
			_actor_manager->RegisterConstActor(result);
			result->OnSpawn();
			if (OnSpawnConstActor)
				OnSpawnConstActor(result);
			return result;
		}
		template<typename type_to_create, typename ...Argv>
			requires std::derived_from<type_to_create, Core::Object::AnimatedActor>
		std::shared_ptr<type_to_create> SpawnAnimatedActor(const Settings::ActorSettings& actor_settings, const Settings::TextureSettings& texture_settings, const Settings::AnimationSettings& animation_settings, Argv && ...argv) {
			std::shared_ptr<type_to_create> result;
			result.reset(new type_to_create(this, actor_settings, texture_settings, animation_settings, std::forward<Argv>(argv)...));
			_actor_manager->RegistrNewActor(result);
			result->OnSpawn();
			if (OnSpawnActor)
				OnSpawnActor(result);
			return result;
		}
		virtual void Draw(sf::RenderWindow& window);
		virtual void Update(float delta);
		virtual void ServiceInput(const Core::Controller::Key& key);
		virtual void InitWorld();
		virtual void EndWorld();
		virtual void CheckCollisionAfterMove(Core::Object::Actor* moved_actor)const;
		virtual void CheckQuit() = 0;
		void CallOnActorsRemoved();
		bool Quit()const;
		void RefreshView(const sf::Vector2f& center)const;
		std::optional<sf::Vector2f> GetMainCharacterPosition()const;
	protected:
		template<typename T>
			requires std::derived_from<T, Component::WorldBaseComponent>
		std::shared_ptr<T> GetTComponent()const {
			for (const auto& component : _world_components) {
				if (auto casted_component = std::dynamic_pointer_cast<T>(component); casted_component)
					return casted_component;
			}
			return {};
		}
		virtual void CreateWorldBaseComponents() = 0;
		virtual void DrawMap(sf::RenderWindow& window) = 0;
		void InitWorldBaseComponents();
		void DrawActors(sf::RenderWindow& window);
		std::function<void(std::shared_ptr<Core::Object::Actor>)> OnSpawnActor;
		std::function<void(std::shared_ptr<Core::Object::Actor>)> OnSpawnConstActor;
		std::function<void()> OnActorsRemoved;
		Engine* _parent = nullptr;
		Settings::WorldSettings _world_settings;
		std::unique_ptr<ActorsManager> _actor_manager;
		std::unique_ptr<Controller::ControllerBase> _main_controller;
		std::list<std::shared_ptr<Component::WorldBaseComponent>> _world_components;
		bool _quit = false;
		bool _initialized = false;
	};
}
