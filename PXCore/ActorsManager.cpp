#include "ActorsManager.h"
#include <functional>
#include <algorithm>
#include <iostream>
#include <future>
#include <math.h>
#include "Object/Actor.h"
namespace Core {
	struct ActorsManager::Impl {
		Impl(size_t init_buffer_size, unsigned gc_delay) :_DELAY{ gc_delay } {
			_actors.rsc->reserve(init_buffer_size);
			_const_actors.rsc->reserve(init_buffer_size);
		}
		void DeleteTagedActors() {
			{
				std::lock_guard lock(_actors.mtx);
				auto it = std::partition(_actors.rsc->begin(), _actors.rsc->end(), [](const std::shared_ptr<Object::Actor>& actor) {
					bool result = actor->ToDestroy();
					if (result)
						actor->OnDelete();
					return result; });
				_actors.rsc->erase(_actors.rsc->begin(), it);
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(_DELAY));
			{
				std::lock_guard lock(_const_actors.mtx);
				auto it = std::partition(_const_actors.rsc->begin(), _const_actors.rsc->end(), [](const std::shared_ptr<Object::Actor>& actor) {
					bool result = actor->ToDestroy();
					if (result)
						actor->OnDelete();
					return result; });
				_const_actors.rsc->erase(_const_actors.rsc->begin(), it);
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(_DELAY));
		}
		void UpdateActors(float delta_time) {
			{
				std::lock_guard lock(_actors.mtx);
				for (auto& actor : *_actors.rsc) {
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
		static std::vector<std::shared_ptr<Object::Actor>> GetCollidableActors(std::vector<std::shared_ptr<Object::Actor>>& input) {
			std::vector<std::shared_ptr<Core::Object::Actor>> result;
			result.reserve(input.size());
			auto last_it = std::partition(input.begin(), input.end(), [](const auto& actor) {
				return actor->CanCollide(); });
			result.insert(result.end(), input.begin(), last_it);
			return result;
		}
		std::vector<std::shared_ptr<Core::Object::Actor>> GetCollidableActors()const {
			auto actors = std::async(std::launch::async, [this]() {return GetCollidableActors(*_actors.rsc); });
			auto const_actors = std::async(std::launch::async, [this]() {return GetCollidableActors(*_const_actors.rsc); });
			std::vector<std::shared_ptr<Object::Actor>> all_actors = actors.get();
			auto const_actors_res = const_actors.get();
			all_actors.insert(all_actors.end(), const_actors_res.begin(), const_actors_res.end());
			return all_actors;
		}
		static sf::Vector2f GetCollisionPush(const sf::FloatRect& input, const sf::RectangleShape& moved_actor, const sf::RectangleShape& touched_actor) {
			sf::Vector2f result(input.width, input.height);
			if (abs(result.x) > abs(result.y)) {
				result.x = .0f;
				if (moved_actor.getPosition().y < touched_actor.getPosition().y)
					result.y *= -1.0f;
			}
			else {
				result.y = .0f;
				if (moved_actor.getPosition().x < touched_actor.getPosition().x)
					result.x *= -1.0f;
			}
			return result;
		}
		void CheckCollisionAfterMove(Core::Object::Actor* moved_actor)const {
			std::lock_guard lock(_actors.mtx);
			std::lock_guard lockc(_const_actors.mtx);
			auto actors = GetCollidableActors();
			for (const auto& actor : actors) {
				sf::FloatRect intersection_area;
				if (moved_actor == actor.get() or !moved_actor->Collide(actor, intersection_area))
					continue;
				auto diference = GetCollisionPush(intersection_area, moved_actor->GetCollider()->GetCollider(), actor->GetCollider()->GetCollider());
				if (moved_actor->GetCollisionType() == actor->GetCollisionType() and moved_actor->GetCollisionType() == ActorsEnums::CollisionType::Collision) {
					moved_actor->OnCollide(actor.get(), diference);
					actor->OnCollide(moved_actor, diference * -1.0f);
				}
				else {
					moved_actor->OnOverlap(actor.get(), diference);
					actor->OnOverlap(moved_actor, diference * -1.0f);
				}
			}
		}
		//pair: k -number of cycles 
		Utility::ThreadingResourceLight<std::vector<std::shared_ptr<Object::Actor>>> _actors;
		Utility::ThreadingResourceLight<std::vector<std::shared_ptr<Object::Actor>>> _const_actors;
		std::unique_ptr<std::thread> _management_thr;
		bool _terminated = false;
		const unsigned _DELAY = 0;
	};
	ActorsManager::ActorsManager(size_t init_buffer_size, unsigned gc_delay) :_impl{ std::make_unique<Impl>(init_buffer_size,gc_delay) } {
		_impl->_management_thr = std::make_unique<std::thread>(std::bind(&ActorsManager::Run, this));
	}
	void ActorsManager::RegistrNewActor(std::shared_ptr<Object::Actor> actor) {
		std::lock_guard lock(_impl->_actors.mtx);
		_impl->_actors.rsc->push_back(actor);
		actor->Init();
	}
	void ActorsManager::RegisterConstActor(std::shared_ptr<Object::Actor> actor) {
		std::lock_guard lock(_impl->_const_actors.mtx);
		_impl->_const_actors.rsc->push_back(actor);
		actor->Init();
	}
	void ActorsManager::RegisterMainActor(std::shared_ptr<Object::Actor> main_actor) {
		std::lock_guard lock(_impl->_actors.mtx);
		_impl->_actors.rsc->push_back(main_actor);
		main_actor->Init();
	}
	void ActorsManager::Update(float delta_time) {
		_impl->UpdateActors(delta_time);
	}
	void ActorsManager::Draw(sf::RenderWindow& window) {
		{
			std::lock_guard lock(_impl->_actors.mtx);
			for (const auto& actor : *_impl->_actors.rsc)
				actor->Draw(window);
		}
		{
			std::lock_guard lock(_impl->_const_actors.mtx);
			for (const auto& actor : *_impl->_const_actors.rsc)
				actor->Draw(window);
		}
	}
	void ActorsManager::CheckCollisionAfterMove(Core::Object::Actor* moved_actor)const {
		_impl->CheckCollisionAfterMove(moved_actor);
	}
	void ActorsManager::Run() {
		while (!_impl->_terminated)
			_impl->DeleteTagedActors();
	}
	void ActorsManager::Terminate() {
		_impl->_terminated = true;
	}
	void ActorsManager::Wait() {
		if (_impl->_management_thr->joinable())
			_impl->_management_thr->join();
	}
}