#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#include "PXUtilities/ThreadingResource.h"
#include "PXUtilities/Interfaces/ILoopingThread.h"
#include "PXSettings/WorldSettings.h"
namespace Core {
	namespace World {
		class WorldBase;
	}
	namespace Object {
		class Actor;
	}
	class ActorsManager :public ILoopingThread {
	public:
		ActorsManager(Core::World::WorldBase* parent, const Settings::WorldSettings& world_settings);
		virtual ~ActorsManager();
		void RegistrNewActor(std::shared_ptr<Object::Actor> actor);
		void RegisterConstActor(std::shared_ptr<Object::Actor> actor);
		void RegisterMainActor(std::shared_ptr<Object::Actor> main_actor);
		void Update(float delta_time);
		void Draw(sf::RenderWindow& window);
		void CheckCollisionAfterMove(Core::Object::Actor* moved_actor)const;
		size_t GetCountOfActors()const;
		// Inherited via IThread
		virtual void Run() override;
		virtual void Terminate()override;
		virtual void Wait()override;
	private:
		struct Impl;
		std::unique_ptr<Impl> _impl;
	};
}
