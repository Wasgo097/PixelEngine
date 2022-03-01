#pragma once
#include "Objects/Actor.h"
#include "Objects/ControlledActor.h"
#include "ActorManager.h"
#include "Settings/WorldSettings.h"
#include "Settings/WindowSettings.h"
namespace Core{
	class World {
	private:
		std::unique_ptr<ActorManager> _actormanager;
		Settings::WorldSettings _worldsettings;
		Settings::WindowSettings _windowsettings;
	public:
		World(const Settings::WorldSettings & worlsettings);
		World(const World&) = delete;
		World(World&&) = delete;
		void operator=(const World&) = delete;
		void operator=(World&&) = delete;
		virtual ~World();
	public:
		template<typename type_to_create, typename ...Argv>
		std::shared_ptr<type_to_create> SpawnActor(const Settings::ActorSettings& actorsettings, const Settings::TextureSettings& texturesettings,Argv && ...argv){
			std::shared_ptr<type_to_create> result;
			type_to_create * ptr = new type_to_create(this, actorsettings, texturesettings,std::forward<Argv>(argv)...);
			result.reset(ptr);
			ptr = nullptr;
			_actormanager->RegistrNewActor(result);
			return result;
		}
		template<typename type_to_create, typename ...Argv>
		std::shared_ptr<type_to_create> SpawnConstActor(const Settings::ActorSettings& actorsettings, const Settings::TextureSettings& texturesettings, Argv && ...argv){
			std::shared_ptr<type_to_create> result;
			type_to_create * ptr = new type_to_create(this, actorsettings, texturesettings,std::forward<Argv>(argv)...);
			result.reset(ptr);
			ptr = nullptr;
			_actormanager->RegisterConstActor(result);
			return result;
		}
		template<typename type_to_create, typename ...Argv>
		std::shared_ptr<type_to_create> SpawnAnimatedActor(const Settings::ActorSettings& actorsettings, const Settings::TextureSettings& texturesettings,const Settings::AnimationSettings& animationsettings, Argv && ...argv) {
			std::shared_ptr<type_to_create> result;
			type_to_create* ptr = new type_to_create(this, actorsettings, texturesettings,animationsettings, std::forward<Argv>(argv)...);
			result.reset(ptr);
			ptr = nullptr;
			_actormanager->RegistrNewActor(result);
			return result;
		}
		void Draw(sf::RenderWindow & window);
		void Update(float delta);
	protected:
		friend class Engine;
		void TermianateActorManager();
		void WaitOnActorManager();
		void RegisterMainCharacter(std::shared_ptr<ControlledActor> mainactor);
	};
}
