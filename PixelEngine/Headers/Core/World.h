#pragma once
#include "CommonHeaders.h"
#include "Objects/Actor.h"
#include "ActorManager.h"
#include "Settings/WorldSettings.h"
#include "Settings/WindowSettings.h"
namespace Core{
	class World final {
	private:
		std::unique_ptr<ActorManager> _actormanager;
		Settings::WorldSettings _worldsettings;
		Settings::WindowSettings _windowsettings;
	public:
		World(Settings::WorldSettings && worlsettings,Settings::WindowSettings&& windowsettings):
			_worldsettings(std::move(worlsettings)),_windowsettings(std::move(windowsettings)),
			_actormanager(std::make_unique<ActorManager>(_worldsettings.BufferSize(), _worldsettings.GcFrequentLevel())){
		}
		World(const World&) = delete;
		World(World&&) = delete;
		void operator=(const World&) = delete;
		void operator=(World&&) = delete;
		~World(){
			_actormanager->Terminate();
			_actormanager->Wait();
		}
	public:
		template<typename type_to_create, typename ...Argv>
		std::shared_ptr<type_to_create> SpawnActor(Argv && ...argv){
			std::shared_ptr<type_to_create> result;
			type_to_create * ptr = new type_to_create(std::forward<Argv>(argv)...);
			result.reset(ptr);
			ptr = nullptr;
			_actormanager->RegistrNewActor(result);
			result->OnSpawn();
			result->OnInit();
			return result;
		}
	};
}
