#pragma once
#include "Utility/ThreadingResource.h"
#include "Types/ILoopingThread.h"
namespace Core{
	class Actor;
	class ActorManager final:public Types::ILoopingThread{
	private:
		void DeleteActors();
		void MoveToSecondStage();
	public:
		ActorManager(size_t buffer_size,int gcfrequentlevel,int cycletomove);
		virtual ~ActorManager() = default;
		void RegistrNewActor(std::shared_ptr<Actor> actor);
		void RegisterConstActor(std::shared_ptr<Actor> actor);
		void RegisterMainActor(std::shared_ptr<Actor> mainactor);
		void UnregisterActor(Actor * actor);
		void Update(float deltatime);
		void Draw(sf::RenderWindow & window);
	public:
		// Inherited via IThread
		virtual void Run() override;
		virtual void Terminate()override;
		virtual void Wait()override;
	private:
		//pair: k -number of cycles 
		Utility::ThreadingResourceLight<std::vector<std::pair<int,std::shared_ptr<Actor>>>> _firststage;
		Utility::ThreadingResourceLight<std::vector<std::shared_ptr<Actor>>> _secondstage;
		Utility::ThreadingResourceLight<std::vector<std::shared_ptr<Actor>>> _constactors;
		const size_t _buffersize;
		const int _frequencylevel;
		const int _cycletomove;
		std::unique_ptr<std::thread> _thread_management;
		bool _terminated = false;
	};
}
