#pragma once
#include "CommonHeaders.h"
#include "Utility/CommonStructures.h"
#include <Objects/Actor.h>
namespace Core{
	class ActorManager{
	private:
		void Loop(){

		}
		void MoveToSecondStage(){

		}
	public:
		ActorManager(size_t buffer_size,int gcfrequentlevel);
		void RegistrNewActor(std::shared_ptr<Actor> actor){
			std::lock_guard lock(_firststage._mtx);
			_firststage._rsc.push_back(std::make_pair(0,actor));
			actor->Init();
		}
		void RegisterConstActor(std::shared_ptr<Actor> actor){
			std::lock_guard lock(_constactor._mtx);
			_constactor._rsc.push_back(actor);
			actor->Init();
		}
		void UnregisterActor(Actor * actor){
			{
				std::lock_guard lock(_firststage._mtx);
				for(auto it = _firststage._rsc.begin(); it != _firststage._rsc.end(); it++){
					if(it->second.get() == actor){
						_firststage._rsc.erase(it);
						return;
					}
				}
			}
			{
				std::lock_guard lock(_secondstage._mtx);
				for(auto it = _secondstage._rsc.begin(); it != _secondstage._rsc.end(); it++){
					if(it->get() == actor){
						_secondstage._rsc.erase(it);
						return;
					}
				}
			}
		}
		void Run(){
			while(true){
				for(int i = 0; i < _frequencylevel; i++){
					{
						std::lock_guard lock(_firststage._mtx);
						for(auto it = _firststage._rsc.begin(); it != _firststage._rsc.end(); it++){
							if(it->second.use_count() == 1||it->second->ToDestroy()){
								_firststage._rsc.erase(it);
								it--;
							}
						}
					}
					std::this_thread::sleep_for(std::chrono::milliseconds(_frequencylevel * 100));
				}
				std::lock_guard lock(_secondstage._mtx);
				for(auto it = _secondstage._rsc.begin(); it != _secondstage._rsc.end(); it++){

				}
			}
		}
	private:
		Utility::ThreadingResourceLight<std::vector<std::pair<int,std::shared_ptr<Actor>>>> _firststage;
		Utility::ThreadingResourceLight<std::vector<std::shared_ptr<Actor>>> _secondstage;
		Utility::ThreadingResourceLight<std::vector<std::shared_ptr<Actor>>> _constactor;
		const int _frequencylevel;
	};
}
