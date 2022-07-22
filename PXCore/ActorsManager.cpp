#include "ActorsManager.h"
#include <functional>
#include <algorithm>
#include <iostream>
#include "Object/Actor.h"
namespace Core {
	struct ActorsManager::Impl {
		Impl(size_t buffer_size, int gc_frequent_level, int cycle_to_move) :
			_management_thr{ std::make_unique<std::thread>(std::bind(&ActorsManager::Run, this)) },
			_BUFFER_SIZE{ buffer_size }, _FREQUENCY_LEVEL{ gc_frequent_level }, _CYCLE_TO_MOVE{ cycle_to_move } {
			_first_stage.rsc->reserve(_BUFFER_SIZE);
			_second_stage.rsc->reserve(_BUFFER_SIZE);
		}
		void DeleteActors() {
			for (int i = 0; i < _FREQUENCY_LEVEL; i++) {
				{
					std::lock_guard lock(_first_stage.mtx);
					auto it = std::partition(_first_stage.rsc->begin(), _first_stage.rsc->end(), [](const std::pair<int, std::shared_ptr<Object::Actor>>& item) {
						bool result = item.second->ToDestroy();
						if (result)
							item.second->OnDelete();
						return result; });
					_first_stage.rsc->erase(_first_stage.rsc->begin(), it);
				}
				std::this_thread::sleep_for(std::chrono::milliseconds(_FREQUENCY_LEVEL * 30));
			}
			{
				std::lock_guard lock(_second_stage.mtx);
				auto it = std::partition(_second_stage.rsc->begin(), _second_stage.rsc->end(), [](const std::shared_ptr<Object::Actor>& item) {
					bool result = item->ToDestroy();
					if (result)
						item->OnDelete();
					return result; });
				_second_stage.rsc->erase(_second_stage.rsc->begin(), it);
				std::this_thread::sleep_for(std::chrono::milliseconds(_FREQUENCY_LEVEL * 30));
			}
		}
		void MoveToSecondStage() {
			std::lock_guard lock(_first_stage.mtx);
			auto& first_stage_rsc = _first_stage.rsc;
			auto it = std::partition(first_stage_rsc->begin(), first_stage_rsc->end(), [this](std::pair<int, std::shared_ptr<Object::Actor>>& element) {
				element.first++;
				return element.first >= _CYCLE_TO_MOVE;
				});
			if (it != first_stage_rsc->begin()) {
				std::lock_guard second_lock(_second_stage.mtx);
				auto& second_stage_rsc = _second_stage.rsc;
				for (auto current_it = first_stage_rsc->begin(); current_it != it; current_it++)
					second_stage_rsc->insert(second_stage_rsc->end(), current_it->second);
				first_stage_rsc->erase(first_stage_rsc->begin(), it);
			}
		}
		void UpdateActors(float delta_time) {
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
		std::vector<std::shared_ptr<Core::Object::Actor>> GetActorsFromFirstStage() {
			std::vector<std::shared_ptr<Core::Object::Actor>> result;
			std::lock_guard lock(_first_stage.mtx);
			result.reserve(_first_stage.rsc->size());
			for (const auto& [_, actor] : *_first_stage.rsc)
				result.push_back(actor);
			return result;
		}
		std::vector<std::shared_ptr<Core::Object::Actor>> GetActors() {
			std::vector<std::shared_ptr<Object::Actor>> all_actors;
			std::lock_guard lock1(_first_stage.mtx);
			const auto& all_actors_from_first_stage = GetActorsFromFirstStage();
			all_actors.reserve(_first_stage.rsc->size());
			all_actors.insert(all_actors.end(), all_actors_from_first_stage.begin(), all_actors_from_first_stage.end());
			std::lock_guard lock2(_second_stage.mtx);
			all_actors.reserve(_second_stage.rsc->size());
			all_actors.insert(all_actors.end(), _second_stage.rsc->begin(), _second_stage.rsc->end());
			std::lock_guard lockc(_const_actors.mtx);
			all_actors.reserve(_const_actors.rsc->size());
			all_actors.insert(all_actors.end(), _const_actors.rsc->begin(), _const_actors.rsc->end());
			return all_actors;
		}
		void CheckCollision() {
			//auto all_actors = GetActors();
		}
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
	ActorsManager::ActorsManager(size_t buffer_size, int gc_frequent_level, int cycle_to_move) :_impl{ std::make_unique<Impl>(buffer_size,gc_frequent_level,cycle_to_move) } {
	}
	void ActorsManager::RegistrNewActor(std::shared_ptr<Object::Actor> actor) {
		std::lock_guard lock(_impl->_first_stage.mtx);
		_impl->_first_stage.rsc->push_back(std::make_pair(0, actor));
		actor->OnSpawn();
		actor->Init();
	}
	void ActorsManager::RegisterConstActor(std::shared_ptr<Object::Actor> actor) {
		std::lock_guard lock(_impl->_const_actors.mtx);
		_impl->_const_actors.rsc->push_back(actor);
		actor->OnSpawn();
		actor->Init();
	}
	void ActorsManager::RegisterMainActor(std::shared_ptr<Object::Actor> main_actor) {
		std::lock_guard lock(_impl->_second_stage.mtx);
		_impl->_second_stage.rsc->push_back(main_actor);
		main_actor->OnSpawn();
		main_actor->Init();
	}
	void ActorsManager::UnregisterActor(Object::Actor* actor) {
		if (actor == nullptr)
			return;
		{
			std::lock_guard lock(_impl->_first_stage.mtx);
			for (auto it = _impl->_first_stage.rsc->begin(); it != _impl->_first_stage.rsc->end(); it++) {
				if (it->second.get() == actor) {
					it->second->OnDelete();
					_impl->_first_stage.rsc->erase(it);
					return;
				}
			}
		}
		{
			std::lock_guard lock(_impl->_second_stage.mtx);
			for (auto it = _impl->_second_stage.rsc->begin(); it != _impl->_second_stage.rsc->end(); it++) {
				if (it->get() == actor) {
					(*it)->OnDelete();
					_impl->_second_stage.rsc->erase(it);
					return;
				}
			}
		}
	}
	void ActorsManager::Update(float delta_time) {
		_impl->UpdateActors(delta_time);
		_impl->CheckCollision();
	}
	void ActorsManager::Draw(sf::RenderWindow& window) {
		{
			std::lock_guard lock(_impl->_first_stage.mtx);
			for (auto& [_, actor] : *_impl->_first_stage.rsc)
				actor->Draw(window);
		}
		{
			std::lock_guard lock(_impl->_second_stage.mtx);
			for (auto& actor : *_impl->_second_stage.rsc)
				actor->Draw(window);
		}
		{
			std::lock_guard lock(_impl->_const_actors.mtx);
			for (auto& actor : *_impl->_const_actors.rsc)
				actor->Draw(window);
		}
	}
	void ActorsManager::Run() {
		while (!_impl->_terminated) {
			_impl->DeleteActors();
			_impl->MoveToSecondStage();
		}
	}
	void ActorsManager::Terminate() {
		_impl->_terminated = true;
	}
	void ActorsManager::Wait() {
		if (_impl->_management_thr->joinable())
			_impl->_management_thr->join();
	}


}