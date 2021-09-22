#include "Core/ActorManager.h"
namespace Core{
	void ActorManager::Loop(){
		for(int i = 0; i < _frequencylevel; i++){
			{
				std::lock_guard lock(_firststage._mtx);
				for(auto it = _firststage._rsc.begin(); it != _firststage._rsc.end(); it++){
					if(/*it->second.use_count() == 1 ||*/ it->second->ToDestroy()){
						_firststage._rsc.erase(it);
						it--;
					}
				}
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(_frequencylevel * 10));
		}
		{
			std::lock_guard lock(_secondstage._mtx);
			for(auto it = _secondstage._rsc.begin(); it != _secondstage._rsc.end(); it++){
				if(/*it->use_count() == 1 ||*/ (*it)->ToDestroy()){
					_secondstage._rsc.erase(it);
					it--;
				}
			}
		}
	}
	void ActorManager::MoveToSecondStage(){
		std::vector<std::shared_ptr<Actor>> actorstomove;
		{
			std::lock_guard lock(_secondstage._mtx);
			actorstomove.reserve((_buffersize - _secondstage._rsc.size()) > 0 ? _buffersize - _secondstage._rsc.size() : 5);
		}
		{
			std::lock_guard lock(_firststage._mtx);
			for(auto it = _firststage._rsc.begin(); it != _firststage._rsc.end(); it++){
				if(it->first >= _cycletomove){
					actorstomove.push_back(it->second);
					_firststage._rsc.erase(it);
					it--;
				}
				else
					(it->first)++;
			}
		}
		std::lock_guard lock(_secondstage._mtx);
		int to_reserve = (_secondstage._rsc.capacity() - _secondstage._rsc.size()) > actorstomove.size() ? 0 : actorstomove.size();
		for(const auto & actor : actorstomove){
			_secondstage._rsc.push_back(actor);
		}
	}
	ActorManager::ActorManager(size_t buffer_size, int gcfrequentlevel, int cycletomove) :
		_buffersize(buffer_size), _frequencylevel(gcfrequentlevel), _cycletomove(cycletomove),
		_actormanagerthr(std::make_unique<std::thread>(&ActorManager::Run, this)){
		_firststage._rsc.reserve(buffer_size);
		_secondstage._rsc.reserve(buffer_size);
		_constactor._rsc.reserve(buffer_size);
	}
	void ActorManager::RegistrNewActor(std::shared_ptr<Actor> actor){
		std::lock_guard lock(_firststage._mtx);
		_firststage._rsc.push_back(std::make_pair(0, actor));
		actor->Init();
	}
	void ActorManager::RegisterConstActor(std::shared_ptr<Actor> actor){
		std::lock_guard lock(_constactor._mtx);
		_constactor._rsc.push_back(actor);
		actor->Init();
	}
	void ActorManager::UnregisterActor(Actor * actor){
		{
			std::lock_guard lock(_firststage._mtx);
			for(auto it = _firststage._rsc.begin(); it != _firststage._rsc.end(); it++){
				if(it->second.get() == actor){
					it->second->OnDelete();
					_firststage._rsc.erase(it);
					return;
				}
			}
		}
		{
			std::lock_guard lock(_secondstage._mtx);
			for(auto it = _secondstage._rsc.begin(); it != _secondstage._rsc.end(); it++){
				if(it->get() == actor){
					(*it)->OnDelete();
					_secondstage._rsc.erase(it);
					return;
				}
			}
		}
	}
	void ActorManager::Run(){
		while(!_termianted){
			Loop();
			MoveToSecondStage();
		}
	}
	void ActorManager::Terminate(){
		_termianted = true;
	}
	void ActorManager::Wait(){
		if(_actormanagerthr->joinable())
			_actormanagerthr->join();
	}
	void ActorManager::Update(float deltatime){}
	void ActorManager::Draw(sf::RenderWindow & window){}
}