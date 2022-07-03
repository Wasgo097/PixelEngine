#include "ActorsManager.h"
#include <functional>
#include <algorithm>
#include "Object/Actor.h"
namespace Core {
	ActorsManager::ActorsManager(size_t buffer_size, int gcfrequentlevel, int cycletomove) :
		_management_thr{ std::make_unique<std::thread>(std::bind(&ActorsManager::Run, this)) },
		_buffer_size{ buffer_size }, _frequency_level{ gcfrequentlevel }, _cycle_to_move{ cycletomove } {
	}
	void ActorsManager::RegistrNewActor(std::shared_ptr<Object::Actor> actor) {
		std::lock_guard lock(_first_stage.mtx);
		_first_stage.rsc->push_back(std::make_pair(0, actor));
		actor->OnSpawn();
		actor->Init();
	}
	void ActorsManager::RegisterConstActor(std::shared_ptr<Object::Actor> actor) {
		std::lock_guard lock(_const_actors.mtx);
		_const_actors.rsc->push_back(actor);
		actor->OnSpawn();
		actor->Init();
	}
	void ActorsManager::RegisterMainActor(std::shared_ptr<Object::Actor> mainactor) {
		std::lock_guard lock(_second_stage.mtx);
		_second_stage.rsc->push_back(mainactor);
		mainactor->OnSpawn();
		mainactor->Init();
	}
	void ActorsManager::UnregisterActor(Object::Actor* actor) {
		if (actor == nullptr)
			return;
		{
			std::lock_guard lock(_first_stage.mtx);
			for (auto it = _first_stage.rsc->begin(); it != _first_stage.rsc->end(); it++) {
				if (it->second.get() == actor) {
					it->second->OnDelete();
					_first_stage.rsc->erase(it);
					return;
				}
			}
		}
		{
			std::lock_guard lock(_second_stage.mtx);
			for (auto it = _second_stage.rsc->begin(); it != _second_stage.rsc->end(); it++) {
				if (it->get() == actor) {
					(*it)->OnDelete();
					_second_stage.rsc->erase(it);
					return;
				}
			}
		}
	}
	void ActorsManager::Update(float delta_time) {
		{
			std::lock_guard lock(_first_stage.mtx);
			for (auto& [_, actor] : *_first_stage.rsc) {
				if (actor->TickFlag())
					actor->Tick(delta_time);
			}
		}
		{
			std::lock_guard lock(_second_stage.mtx);
			for (auto& actor : *_second_stage.rsc) {
				if (actor->TickFlag())
					actor->Tick(delta_time);
			}
		}
		{
			std::lock_guard lock(_const_actors.mtx);
			for (auto& actor : *_const_actors.rsc) {
				if (actor->TickFlag())
					actor->Tick(delta_time);
			}
		}
	}
	void ActorsManager::Draw(sf::RenderWindow& window) {
		{
			std::lock_guard lock(_first_stage.mtx);
			for (auto& [_, actor] : *_first_stage.rsc)
				actor->Draw(window);
		}
		{
			std::lock_guard lock(_second_stage.mtx);
			for (auto& actor : *_second_stage.rsc)
				actor->Draw(window);
		}
		{
			std::lock_guard lock(_const_actors.mtx);
			for (auto& actor : *_const_actors.rsc)
				actor->Draw(window);
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

	void ActorsManager::DeleteActors() {
		for (int i = 0; i < _frequency_level; i++) {
			{
				std::lock_guard lock(_first_stage.mtx);
				auto it = std::partition(_first_stage.rsc->begin(), _first_stage.rsc->end(), [](const std::pair<int, std::shared_ptr<Object::Actor>>& item) {
					bool result = item.second->ToDestroy();
					if (result)
						item.second->OnDelete();
					return result; });
				_first_stage.rsc->erase(_first_stage.rsc->begin(), it);
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(_frequency_level * 30));
		}
		{
			std::lock_guard lock(_second_stage.mtx);
			auto it = std::partition(_second_stage.rsc->begin(), _second_stage.rsc->end(), [](const std::shared_ptr<Object::Actor>& item) {
				bool result = item->ToDestroy();
				if (result)
					item->OnDelete();
				return result; });
			_second_stage.rsc->erase(_second_stage.rsc->begin(), it);
			std::this_thread::sleep_for(std::chrono::milliseconds(_frequency_level * 30));
		}
	}
	void ActorsManager::MoveToSecondStage() {
		{
			std::lock_guard lock(_first_stage.mtx);
			//for (auto it = _first_stage.rsc->begin(); it != _first_stage.rsc->end(); it++) {
			//	if (it->first >= _cycle_to_move) {
			//		actors_to_move.push_back(it->second);
			//		_first_stage.rsc->erase(it);
			//		it--;
			//	}
			//	else
			//		(it->first)++;
			//}
			auto it = std::partition(_first_stage.rsc->begin(), _first_stage.rsc->end(), [this](std::pair<int, std::shared_ptr<Object::Actor>>& element) {
				element.first++;
				return element.first >= _cycle_to_move;
				});
			//use move iterator 
		}
		{
			std::lock_guard lock(_second_stage.mtx);
			/*int to_reserve = (_second_stage.rsc->capacity() - _second_stage.rsc->size()) > actors_to_move.size() ? 0 : actors_to_move.size();
			if (to_reserve > 0)
				_second_stage.rsc->reserve(to_reserve);
			for (const auto& actor : actors_to_move) {
				_second_stage.rsc->push_back(actor);
			}*/
		}
	}
}