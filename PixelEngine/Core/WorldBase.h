#pragma once
#include <stack>
#include "Objects/Actor.h"
#include "Objects/ControlledActor.h"
#include "ActorManager.h"
#include "Settings/WorldSettings.h"
namespace Core{
	class Engine;
	class WorldBase {
	public:
		WorldBase(const Settings::WorldSettings & worlsettings=Settings::WorldSettings(),Engine* parrent=nullptr);
		WorldBase(const WorldBase&) = delete;
		WorldBase(WorldBase&&) = delete;
		void operator=(const WorldBase&) = delete;
		void operator=(WorldBase&&) = delete;
		virtual ~WorldBase();
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
		virtual void Draw(sf::RenderWindow & window);
		virtual void Update(float delta);
		void SetParrnet(Engine* parrent);
		bool Quit()const;
		virtual void ServiceInput(sf::Event event);
	protected:
		Engine* _parrent = nullptr;
	protected:
		Settings::WorldSettings _worldsettings;
		std::unique_ptr<ActorManager> _actormanager;
		std::unique_ptr<Controller::ControllerBase> _maincontroller;
		bool _quit = false;
	protected:
		virtual void CheckQuit() = 0;
		virtual void InitWorld() = 0;
		virtual void EndWorld() = 0;
	};
}
