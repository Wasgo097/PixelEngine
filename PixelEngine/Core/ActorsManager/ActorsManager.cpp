#include "Utility/CommonHeaders.h"
#include "ActorsManager.h"
#include <Objects/Actor.h>
namespace Core {
	void ActorsManager::DeleteActors() {
		for (int i = 0; i < _frequencylevel; i++) {
			{
				std::lock_guard lock(_firststage.Mtx);
				for (auto it = _firststage.Rsc.begin(); it != _firststage.Rsc.end(); it++) {
					if (it->second->ToDestroy()) {
						it->second->OnDelete();
						_firststage.Rsc.erase(it);
						it--;
					}
				}
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(_frequencylevel * 30));
		}
		{
			std::lock_guard lock(_secondstage.Mtx);
			for (auto it = _secondstage.Rsc.begin(); it != _secondstage.Rsc.end(); it++) {
				if ((*it)->ToDestroy()) {
					(*it)->OnDelete();
					_secondstage.Rsc.erase(it);
					it--;
				}
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(_frequencylevel * 30));
		}
	}
	void ActorsManager::MoveToSecondStage() {
		std::vector<std::shared_ptr<Actor>> actorstomove;
		{
			std::lock_guard lock(_secondstage.Mtx);
			size_t to_reserve = (_buffersize - _secondstage.Rsc.size()) > 0 ? _buffersize - _secondstage.Rsc.size() : 5;
			actorstomove.reserve(to_reserve);
		}
		{
			std::lock_guard lock(_firststage.Mtx);
			for (auto it = _firststage.Rsc.begin(); it != _firststage.Rsc.end(); it++) {
				if (it->first >= _cycletomove) {
					actorstomove.push_back(it->second);
					_firststage.Rsc.erase(it);
					it--;
				}
				else
					(it->first)++;
			}
		}
		{
			std::lock_guard lock(_secondstage.Mtx);
			int to_reserve = (_secondstage.Rsc.capacity() - _secondstage.Rsc.size()) > actorstomove.size() ? 0 : actorstomove.size();
			if (to_reserve > 0)
				_secondstage.Rsc.reserve(to_reserve);
			for (const auto& actor : actorstomove) {
				_secondstage.Rsc.push_back(actor);
			}
		}
	}
	ActorsManager::ActorsManager(size_t buffer_size, int gcfrequentlevel, int cycletomove) :
		_thread_management(std::make_unique<std::thread>(std::bind(&ActorsManager::Run, this))),
		_buffersize(buffer_size), _frequencylevel(gcfrequentlevel), _cycletomove(cycletomove) {
		_firststage.Rsc.reserve(_buffersize);
		_secondstage.Rsc.reserve(_buffersize);
		_constactors.Rsc.reserve(_buffersize);
	}
	void ActorsManager::RegistrNewActor(std::shared_ptr<Actor> actor) {
		std::lock_guard lock(_firststage.Mtx);
		_firststage.Rsc.push_back(std::make_pair(0, actor));
		actor->OnSpawn();
		actor->Init();
	}
	void ActorsManager::RegisterConstActor(std::shared_ptr<Actor> actor) {
		std::lock_guard lock(_constactors.Mtx);
		_constactors.Rsc.push_back(actor);
		actor->OnSpawn();
		actor->Init();
	}
	void ActorsManager::RegisterMainActor(std::shared_ptr<Actor> mainactor){
		std::lock_guard lock(_secondstage.Mtx);
		_secondstage.Rsc.push_back(mainactor);
		mainactor->OnSpawn();
		mainactor->Init();
	}
	void ActorsManager::UnregisterActor(Actor* actor) {
		if (actor == nullptr)
			return;
		{
			std::lock_guard lock(_firststage.Mtx);
			for (auto it = _firststage.Rsc.begin(); it != _firststage.Rsc.end(); it++) {
				if (it->second.get() == actor) {
					it->second->OnDelete();
					_firststage.Rsc.erase(it);
					return;
				}
			}
		}
		{
			std::lock_guard lock(_secondstage.Mtx);
			for (auto it = _secondstage.Rsc.begin(); it != _secondstage.Rsc.end(); it++) {
				if (it->get() == actor) {
					(*it)->OnDelete();
					_secondstage.Rsc.erase(it);
					return;
				}
			}
		}
	}
	void ActorsManager::Run() {
		while (!_terminated) {
			DeleteActors();
			MoveToSecondStage();
		}
	}
	void ActorsManager::Terminate() {
		_terminated = true;
	}
	void ActorsManager::Wait() {
		if (_thread_management->joinable())
			_thread_management->join();
	}
	void ActorsManager::Update(float deltatime) {
		{
			std::lock_guard lock(_firststage.Mtx);
			for (auto& [Cycle, Actor] : _firststage.Rsc) {
				if (Actor->TickFlag())
					Actor->Tick(deltatime);
			}
		}
		{
			std::lock_guard lock(_secondstage.Mtx);
			for (auto& Actor : _secondstage.Rsc) {
				if (Actor->TickFlag())
					Actor->Tick(deltatime);
			}
		}
		{
			std::lock_guard lock(_constactors.Mtx);
			for (auto& Actor : _constactors.Rsc) {
				if (Actor->TickFlag())
					Actor->Tick(deltatime);
			}
		}
	}
	void ActorsManager::Draw(sf::RenderWindow& window) {
		{
			std::lock_guard lock(_firststage.Mtx);
			for (auto& [Key, Value] : _firststage.Rsc) {
				Value->Draw(window);
			}
		}
		{
			std::lock_guard lock(_secondstage.Mtx);
			for (auto& Actor : _secondstage.Rsc) {
				Actor->Draw(window);
			}
		}
		{
			std::lock_guard lock(_constactors.Mtx);
			for (auto& Actor : _constactors.Rsc) {
				Actor->Draw(window);
			}
		}
	}
}