#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#include "PXUtilities/ThreadingResource.h"
#include "PXUtilities/Interfaces/ILoopingThread.h"
namespace Core {
	namespace Object {
		class Actor;
	}
	class ActorsManager :public ILoopingThread {
	public:
		ActorsManager(size_t init_buffer_size,unsigned gc_delay);
		virtual ~ActorsManager() = default;
		void RegistrNewActor(std::shared_ptr<Object::Actor> actor);
		void RegisterConstActor(std::shared_ptr<Object::Actor> actor);
		void RegisterMainActor(std::shared_ptr<Object::Actor> main_actor);
		void Update(float delta_time);
		void Draw(sf::RenderWindow& window);
		void CheckCollisionAfterMove(Core::Object::Actor* moved_actor)const;
		// Inherited via IThread
		virtual void Run() override;
		virtual void Terminate()override;
		virtual void Wait()override;
	private:
		struct Impl;
		std::unique_ptr<Impl> _impl;
	};
}
