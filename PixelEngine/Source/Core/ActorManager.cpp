#include "CommonHeaders.h"
#include "Core/ActorManager.h"
#include <Objects/Actor.h>
namespace Core {
	void ActorManager::DeleteActors() {
		for (int i = 0; i < _frequencylevel; i++) {
			{
				std::lock_guard lock(_firststage._mtx);
				for (auto it = _firststage._rsc.begin(); it != _firststage._rsc.end(); it++) {
					if (it->second->ToDestroy()) {
						it->second->OnDelete();
						_firststage._rsc.erase(it);
						it--;
					}
				}
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(_frequencylevel * 30));
		}
		{
			std::lock_guard lock(_secondstage._mtx);
			for (auto it = _secondstage._rsc.begin(); it != _secondstage._rsc.end(); it++) {
				if ((*it)->ToDestroy()) {
					(*it)->OnDelete();
					_secondstage._rsc.erase(it);
					it--;
				}
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(_frequencylevel * 30));
		}
	}
	void ActorManager::MoveToSecondStage() {
		std::vector<std::shared_ptr<Actor>> actorstomove;
		{
			std::lock_guard lock(_secondstage._mtx);
			size_t to_reserve = (_buffersize - _secondstage._rsc.size()) > 0 ? _buffersize - _secondstage._rsc.size() : 5;
			actorstomove.reserve(to_reserve);
		}
		{
			std::lock_guard lock(_firststage._mtx);
			for (auto it = _firststage._rsc.begin(); it != _firststage._rsc.end(); it++) {
				if (it->first >= _cycletomove) {
					actorstomove.push_back(it->second);
					_firststage._rsc.erase(it);
					it--;
				}
				else
					(it->first)++;
			}
		}
		{
			std::lock_guard lock(_secondstage._mtx);
			int to_reserve = (_secondstage._rsc.capacity() - _secondstage._rsc.size()) > actorstomove.size() ? 0 : actorstomove.size();
			if (to_reserve > 0)
				_secondstage._rsc.reserve(to_reserve);
			for (const auto& actor : actorstomove) {
				_secondstage._rsc.push_back(actor);
			}
		}
	}
	ActorManager::ActorManager(size_t buffer_size, int gcfrequentlevel, int cycletomove) :
		_thread_management(std::make_unique<std::thread>(std::bind(&ActorManager::Run, this))),
		_buffersize(buffer_size), _frequencylevel(gcfrequentlevel), _cycletomove(cycletomove) {
		_firststage._rsc.reserve(_buffersize);
		_secondstage._rsc.reserve(_buffersize);
		_constactors._rsc.reserve(_buffersize);
	}
	void ActorManager::RegistrNewActor(std::shared_ptr<Actor> actor) {
		std::lock_guard lock(_firststage._mtx);
		_firststage._rsc.push_back(std::make_pair(0, actor));
		actor->OnSpawn();
		actor->Init();
	}
	void ActorManager::RegisterConstActor(std::shared_ptr<Actor> actor) {
		std::lock_guard lock(_constactors._mtx);
		_constactors._rsc.push_back(actor);
		actor->OnSpawn();
		actor->Init();
	}
	void ActorManager::RegisterMainActor(std::shared_ptr<Actor> mainactor){
		std::lock_guard lock(_secondstage._mtx);
		_secondstage._rsc.push_back(mainactor);
		mainactor->OnSpawn();
		mainactor->Init();
	}
	void ActorManager::UnregisterActor(Actor* actor) {
		if (actor == nullptr)
			return;
		{
			std::lock_guard lock(_firststage._mtx);
			for (auto it = _firststage._rsc.begin(); it != _firststage._rsc.end(); it++) {
				if (it->second.get() == actor) {
					it->second->OnDelete();
					_firststage._rsc.erase(it);
					return;
				}
			}
		}
		{
			std::lock_guard lock(_secondstage._mtx);
			for (auto it = _secondstage._rsc.begin(); it != _secondstage._rsc.end(); it++) {
				if (it->get() == actor) {
					(*it)->OnDelete();
					_secondstage._rsc.erase(it);
					return;
				}
			}
		}
	}
	void ActorManager::Run() {
		while (!_terminated) {
			DeleteActors();
			MoveToSecondStage();
		}
	}
	void ActorManager::Terminate() {
		_terminated = true;
	}
	void ActorManager::Wait() {
		if (_thread_management->joinable())
			_thread_management->join();
	}
	void ActorManager::Update(float deltatime) {
		{
			std::lock_guard lock(_firststage._mtx);
			for (auto& [Key, Value] : _firststage._rsc) {
				if (Value->TickFlag() == true)
					Value->Tick(deltatime);
			}
		}
		{
			std::lock_guard lock(_secondstage._mtx);
			for (auto& Actor : _secondstage._rsc) {
				if (Actor->TickFlag() == true)
					Actor->Tick(deltatime);
			}
		}
		{
			std::lock_guard lock(_constactors._mtx);
			for (auto& Actor : _constactors._rsc) {
				if (Actor->TickFlag() == true)
					Actor->Tick(deltatime);
			}
		}
	}
	void ActorManager::Draw(sf::RenderWindow& window) {
		{
			std::lock_guard lock(_firststage._mtx);
			for (auto& [Key, Value] : _firststage._rsc) {
				Value->Draw(window);
			}
		}
		{
			std::lock_guard lock(_secondstage._mtx);
			for (auto& Actor : _secondstage._rsc) {
				Actor->Draw(window);
			}
		}
		{
			std::lock_guard lock(_constactors._mtx);
			for (auto& Actor : _constactors._rsc) {
				Actor->Draw(window);
			}
		}
	}
}