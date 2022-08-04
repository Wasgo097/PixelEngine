#include "ActorsManager.h"
#include <functional>
#include <algorithm>
#include <future>
#include <math.h>
#include "Object/Actor.h"
#include "PXCore/World/WorldBase.h"
namespace Core {
	struct ActorsManager::Impl {
		Impl(Core::World::WorldBase* parent, const Settings::WorldSettings& world_settings) :
			DELAY{ world_settings.gc_delay }, parent{ parent }, deadzone{ world_settings.deadzone_x,world_settings.deadzone_y }{
			actors.rsc->reserve(world_settings.buffer_size);
			const_actors.rsc->reserve(world_settings.buffer_size);
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
		static std::vector<std::shared_ptr<Object::Actor>> GetCollidableActors(std::vector<std::shared_ptr<Object::Actor>>& input) {
			std::vector<std::shared_ptr<Core::Object::Actor>> result;
			result.reserve(input.size());
			auto last_it = std::partition(input.begin(), input.end(), [](const auto& actor) {
				return actor->CanCollide(); });
			result.insert(result.end(), input.begin(), last_it);
			return result;
		}
		bool PositionOnDeadzone(const sf::Vector2f& position)const {
			return position.x < -std::abs(deadzone.x) or position.x > std::abs(deadzone.x) or position.y < -std::abs(deadzone.y) or position.y > std::abs(deadzone.y);
		}
		void DeleteActors() {
			{
				std::lock_guard lock(actors.mtx);
				auto it = std::partition(actors.rsc->begin(), actors.rsc->end(), [this](const std::shared_ptr<Object::Actor>& actor) {
					bool result = actor->ToDestroy();
					if (result)
						actor->OnDelete();
					else if (auto position = actor->GetPosition(); position and PositionOnDeadzone(*position)) {
						actor->OnDelete();
						result = true;
					}
					return result; });
				if (actors.rsc->begin() != it) {
					actors.rsc->erase(actors.rsc->begin(), it);
					parent->CallOnActorsRemoved();
				}
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
			{
				std::lock_guard lock(const_actors.mtx);
				auto it = std::partition(const_actors.rsc->begin(), const_actors.rsc->end(), [](const std::shared_ptr<Object::Actor>& actor) {
					bool result = actor->ToDestroy();
					if (result)
						actor->OnDelete();
					return result; });
				const_actors.rsc->erase(const_actors.rsc->begin(), it);
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
		}
		void UpdateActors(float delta_time) {
			{
				std::lock_guard lock(actors.mtx);
				for (auto& actor : *actors.rsc) {
					if (actor->TickFlag())
						actor->Tick(delta_time);
				}
			}
			{
				std::lock_guard lock(const_actors.mtx);
				for (auto& actor : *const_actors.rsc) {
					if (actor->TickFlag())
						actor->Tick(delta_time);
				}
			}
		}
		std::vector<std::shared_ptr<Core::Object::Actor>> GetCollidableActors()const {
			auto collidable_actors = std::async(std::launch::async, [this]() {return GetCollidableActors(*actors.rsc); });
			auto collidable_const_actors = std::async(std::launch::async, [this]() {return GetCollidableActors(*const_actors.rsc); });
			std::vector<std::shared_ptr<Object::Actor>> all_actors = collidable_actors.get();
			auto const_actors_res = collidable_const_actors.get();
			all_actors.insert(all_actors.end(), const_actors_res.begin(), const_actors_res.end());
			return all_actors;
		}
		void CheckCollisionAfterMove(Core::Object::Actor* moved_actor)const {
			std::lock_guard lock(actors.mtx);
			std::lock_guard lockc(const_actors.mtx);
			auto actors = GetCollidableActors();
			for (const auto& actor : actors) {
				sf::FloatRect intersection_area;
				if (moved_actor == actor.get() or !moved_actor->Collide(actor, intersection_area))
					continue;
				auto diference = GetCollisionPush(intersection_area, moved_actor->GetColliderComponent()->GetCollider(), actor->GetColliderComponent()->GetCollider());
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
		size_t GetCountOfActors()const {
			std::lock_guard lock(actors.mtx);
			return actors.rsc->size();
		}
		std::unique_ptr<std::thread> management_thr;
		Utility::ThreadingResourceLight<std::vector<std::shared_ptr<Object::Actor>>> actors;
		Utility::ThreadingResourceLight<std::vector<std::shared_ptr<Object::Actor>>> const_actors;
		Core::World::WorldBase* parent;
		bool terminated = false;
		const unsigned DELAY = 0;
		sf::Vector2f deadzone;
	};
	ActorsManager::ActorsManager(Core::World::WorldBase* parent, const Settings::WorldSettings& world_settings) :_impl{ std::make_unique<Impl>(parent, world_settings) } {
		_impl->management_thr = std::make_unique<std::thread>(std::bind(&ActorsManager::Run, this));
	}
	ActorsManager::~ActorsManager() {
		Terminate();
		Wait();
	}
	void ActorsManager::RegistrNewActor(std::shared_ptr<Object::Actor> actor) {
		std::lock_guard lock(_impl->actors.mtx);
		_impl->actors.rsc->push_back(actor);
		actor->Init();
	}
	void ActorsManager::RegisterConstActor(std::shared_ptr<Object::Actor> actor) {
		std::lock_guard lock(_impl->const_actors.mtx);
		_impl->const_actors.rsc->push_back(actor);
		actor->Init();
	}
	void ActorsManager::RegisterMainActor(std::shared_ptr<Object::Actor> main_actor) {
		std::lock_guard lock(_impl->actors.mtx);
		_impl->actors.rsc->push_back(main_actor);
		main_actor->Init();
	}
	void ActorsManager::Update(float delta_time) {
		_impl->UpdateActors(delta_time);
	}
	void ActorsManager::Draw(sf::RenderWindow& window) {
		{
			static std::function<bool(const std::shared_ptr<const Core::Object::Actor>&,
				const std::shared_ptr<const Core::Object::Actor>&)> actors_comparator =
				[](const std::shared_ptr<const Core::Object::Actor>& first, const std::shared_ptr<const Core::Object::Actor>& second) {
				if (auto first_pos = first->GetPosition(); first_pos)
					if (auto second_pos = second->GetPosition(); second_pos)
						return static_cast<int>(first_pos->y) < static_cast<int>(second_pos->y);
				return true;
			};
			std::lock_guard lock(_impl->actors.mtx);
			if (!std::is_sorted(_impl->actors.rsc->begin(), _impl->actors.rsc->end(), actors_comparator))
				std::sort(_impl->actors.rsc->begin(), _impl->actors.rsc->end(), actors_comparator);
			for (const auto& actor : *_impl->actors.rsc)
				actor->Draw(window);
		}
		//{
		//	std::lock_guard lock(_impl->_const_actors.mtx);
		//	for (const auto& actor : *_impl->_const_actors.rsc)
		//		actor->Draw(window);
		//}
	}
	void ActorsManager::CheckCollisionAfterMove(Core::Object::Actor* moved_actor)const {
		_impl->CheckCollisionAfterMove(moved_actor);
	}
	size_t ActorsManager::GetCountOfActors() const {
		return _impl->GetCountOfActors();
	}
	void ActorsManager::Run() {
		while (!_impl->terminated)
			_impl->DeleteActors();
	}
	void ActorsManager::Terminate() {
		_impl->terminated = true;
	}
	void ActorsManager::Wait() {
		if (_impl->management_thr->joinable())
			_impl->management_thr->join();
	}
}