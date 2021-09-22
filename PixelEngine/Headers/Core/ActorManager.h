#pragma once
#include "CommonHeaders.h"
#include "Utility/CommonStructures.h"
#include <Objects/Actor.h>
namespace Core{
	class ActorManager final{
	private:
		void Loop();
		void MoveToSecondStage();
	public:
		ActorManager(size_t buffer_size,int gcfrequentlevel,int cycletomove);
		void RegistrNewActor(std::shared_ptr<Actor> actor);
		void RegisterConstActor(std::shared_ptr<Actor> actor);
		void UnregisterActor(Actor * actor);
		void Run();
		void Terminate ();
		void Wait ();
		void Update(float deltatime);
		void Draw(sf::RenderWindow & window);
	private:
		//pair: k -number of cycles 
		Utility::ThreadingResourceLight<std::vector<std::pair<int,std::shared_ptr<Actor>>>> _firststage;
		Utility::ThreadingResourceLight<std::vector<std::shared_ptr<Actor>>> _secondstage;
		Utility::ThreadingResourceLight<std::vector<std::shared_ptr<Actor>>> _constactor;
		const size_t _buffersize;
		const int _frequencylevel;
		const int _cycletomove;
		bool _termianted = false;
		std::unique_ptr<std::thread> _actormanagerthr;
	};
}
