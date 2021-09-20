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
		World(const Settings::WorldSettings & worlsettings, const Settings::WindowSettings& windowsettings);
		World(const World&) = delete;
		World(World&&) = delete;
		void operator=(const World&) = delete;
		void operator=(World&&) = delete;
		~World();
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
