#include "Utility/CommonHeaders.h"
#include "ActorsManager.h"
#include <Objects/Actor.h>
namespace Core {
	void ActorsManager::DeleteActors() {
		for (int i = 0; i < _frequency_level; i++) {
			{
				std::lock_guard lock(_first_stage.Mtx);
				for (auto it = _first_stage.Rsc.begin(); it != _first_stage.Rsc.end(); it++) {
					if (it->second->ToDestroy()) {
						it->second->OnDelete();
						_first_stage.Rsc.erase(it);
						it--;
					}
				}
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(_frequency_level * 30));
		}
		{
			std::lock_guard lock(_second_stage.Mtx);
			for (auto it = _second_stage.Rsc.begin(); it != _second_stage.Rsc.end(); it++) {
				if ((*it)->ToDestroy()) {
					(*it)->OnDelete();
					_second_stage.Rsc.erase(it);
					it--;
				}
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(_frequency_level * 30));
		}
	}
	void ActorsManager::MoveToSecondStage() {
		std::vector<std::shared_ptr<Actor>> actors_to_move;
		{
			std::lock_guard lock(_second_stage.Mtx);
			size_t to_reserve = (_buffer_size - _second_stage.Rsc.size()) > 0 ? _buffer_size - _second_stage.Rsc.size() : 5;
			actors_to_move.reserve(to_reserve);
		}
		{
			std::lock_guard lock(_first_stage.Mtx);
			for (auto it = _first_stage.Rsc.begin(); it != _first_stage.Rsc.end(); it++) {
				if (it->first >= _cycle_to_move) {
					actors_to_move.push_back(it->second);
					_first_stage.Rsc.erase(it);
					it--;
				}
				else
					(it->first)++;
			}
		}
		{
			std::lock_guard lock(_second_stage.Mtx);
			int to_reserve = (_second_stage.Rsc.capacity() - _second_stage.Rsc.size()) > actors_to_move.size() ? 0 : actors_to_move.size();
			if (to_reserve > 0)
				_second_stage.Rsc.reserve(to_reserve);
			for (const auto& actor : actors_to_move) {
				_second_stage.Rsc.push_back(actor);
			}
		}
	}
	ActorsManager::ActorsManager(size_t buffer_size, int gcfrequentlevel, int cycletomove) :
		_management_thr(std::make_unique<std::thread>(std::bind(&ActorsManager::Run, this))),
		_buffer_size(buffer_size), _frequency_level(gcfrequentlevel), _cycle_to_move(cycletomove) {
		_first_stage.Rsc.reserve(_buffer_size);
		_second_stage.Rsc.reserve(_buffer_size);
		_const_actors.Rsc.reserve(_buffer_size);
	}
	void ActorsManager::RegistrNewActor(std::shared_ptr<Actor> actor) {
		std::lock_guard lock(_first_stage.Mtx);
		_first_stage.Rsc.push_back(std::make_pair(0, actor));
		actor->OnSpawn();
		actor->Init();
	}
	void ActorsManager::RegisterConstActor(std::shared_ptr<Actor> actor) {
		std::lock_guard lock(_const_actors.Mtx);
		_const_actors.Rsc.push_back(actor);
		actor->OnSpawn();
		actor->Init();
	}
	void ActorsManager::RegisterMainActor(std::shared_ptr<Actor> mainactor){
		std::lock_guard lock(_second_stage.Mtx);
		_second_stage.Rsc.push_back(mainactor);
		mainactor->OnSpawn();
		mainactor->Init();
	}
	void ActorsManager::UnregisterActor(Actor* actor) {
		if (actor == nullptr)
			return;
		{
			std::lock_guard lock(_first_stage.Mtx);
			for (auto it = _first_stage.Rsc.begin(); it != _first_stage.Rsc.end(); it++) {
				if (it->second.get() == actor) {
					it->second->OnDelete();
					_first_stage.Rsc.erase(it);
					return;
				}
			}
		}
		{
			std::lock_guard lock(_second_stage.Mtx);
			for (auto it = _second_stage.Rsc.begin(); it != _second_stage.Rsc.end(); it++) {
				if (it->get() == actor) {
					(*it)->OnDelete();
					_second_stage.Rsc.erase(it);
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
		if (_management_thr->joinable())
			_management_thr->join();
	}
	void ActorsManager::Update(float deltatime) {
		{
			std::lock_guard lock(_first_stage.Mtx);
			for (auto& [_, actor] : _first_stage.Rsc) {
				if (actor->TickFlag())
					actor->Tick(deltatime);
			}
		}
		{
			std::lock_guard lock(_second_stage.Mtx);
			for (auto& actor : _second_stage.Rsc) {
				if (actor->TickFlag())
					actor->Tick(deltatime);
			}
		}
		{
			std::lock_guard lock(_const_actors.Mtx);
			for (auto& actor : _const_actors.Rsc) {
				if (actor->TickFlag())
					actor->Tick(deltatime);
			}
		}
	}
	void ActorsManager::Draw(sf::RenderWindow& window) {
		{
			std::lock_guard lock(_first_stage.Mtx);
			for (auto& [_, actor] : _first_stage.Rsc) {
				actor->Draw(window);
			}
		}
		{
			std::lock_guard lock(_second_stage.Mtx);
			for (auto& actor : _second_stage.Rsc) {
				actor->Draw(window);
			}
		}
		{
			std::lock_guard lock(_const_actors.Mtx);
			for (auto& actor : _const_actors.Rsc) {
				actor->Draw(window);
			}
		}
	}
}