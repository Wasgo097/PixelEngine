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
		ActorsManager(size_t buffer_size, int gc_frequent_level, int cycle_to_move);
		virtual ~ActorsManager() = default;
		void RegistrNewActor(std::shared_ptr<Object::Actor> actor);
		void RegisterConstActor(std::shared_ptr<Object::Actor> actor);
		void RegisterMainActor(std::shared_ptr<Object::Actor> main_actor);
		void UnregisterActor(Object::Actor* actor);
		void Update(float delta_time);
		void Draw(sf::RenderWindow& window);
		// Inherited via IThread
		virtual void Run() override;
		virtual void Terminate()override;
		virtual void Wait()override;
	private:
		void DeleteActors();
		void MoveToSecondStage();
		//pair: k -number of cycles 
		Utility::ThreadingResourceLight<std::vector<std::pair<int, std::shared_ptr<Object::Actor>>>> _first_stage;
		Utility::ThreadingResourceLight<std::vector<std::shared_ptr<Object::Actor>>> _second_stage;
		Utility::ThreadingResourceLight<std::vector<std::shared_ptr<Object::Actor>>> _const_actors;
		const size_t _BUFFER_SIZE;
		const int _FREQUENCY_LEVEL;
		const int _CYCLE_TO_MOVE;
		std::unique_ptr<std::thread> _management_thr;
		bool _terminated = false;
	};
}
