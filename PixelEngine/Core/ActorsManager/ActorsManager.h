#pragma once
#include "Utility/ThreadingResource.h"
#include "Interfaces/ILoopingThread.h"
namespace Core{
	class Actor;
	class ActorsManager:public Types::ILoopingThread{
	public:
		ActorsManager(size_t buffer_size,int gc_frequent_level,int cycle_to_move);
		virtual ~ActorsManager() = default;
		void RegistrNewActor(std::shared_ptr<Actor> actor);
		void RegisterConstActor(std::shared_ptr<Actor> actor);
		void RegisterMainActor(std::shared_ptr<Actor> main_actor);
		void UnregisterActor(Actor * actor);
		void Update(float delta);
		void Draw(sf::RenderWindow & window);
		// Inherited via IThread
		virtual void Run() override;
		virtual void Terminate()override;
		virtual void Wait()override;
	private:
		void DeleteActors();
		void MoveToSecondStage();
		//pair: k -number of cycles 
		Utility::ThreadingResourceLight<std::vector<std::pair<int,std::shared_ptr<Actor>>>> _first_stage;
		Utility::ThreadingResourceLight<std::vector<std::shared_ptr<Actor>>> _second_stage;
		Utility::ThreadingResourceLight<std::vector<std::shared_ptr<Actor>>> _const_actors;
		const size_t _buffer_size;
		const int _frequency_level;
		const int _cycle_to_move;
		std::unique_ptr<std::thread> _management_thr;
		bool _terminated = false;
	};
}
