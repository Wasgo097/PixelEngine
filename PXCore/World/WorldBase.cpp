#include "WorldBase.h"
#include <iostream>
#include "ActorsManager.h"
#include "Controller/ControllerBase.h"
#include "Engine.h"
namespace Core::World {
	WorldBase::WorldBase(const Settings::WorldSettings& world_settings, Engine* parent) :_parent(parent),
		_world_settings(world_settings), _actor_manager(std::make_unique<ActorsManager>(this, world_settings)) {
	}
	void WorldBase::Draw(sf::RenderWindow& window) {
		if (!_initialized)
			throw std::runtime_error("Draw uninitialized world");
		window.clear(sf::Color::Green);
		if (_actor_manager)
			_actor_manager->Draw(window);
	}
	void WorldBase::Update(float delta) {
		if (!_initialized)
			throw std::runtime_error("Update uninitialized world");
		if (delta > 0.2)
			std::cerr << "WARNING! Tick time above save value! Current delta: " << delta << "\n";
		if (_actor_manager)
			_actor_manager->Update(delta);
		for (const auto& component : _world_components)
			if (component->TickFlag())
				component->Tick(delta);
	}
	void WorldBase::CheckCollisionAfterMove(Core::Object::Actor* moved_actor)const {
		_actor_manager->CheckCollisionAfterMove(moved_actor);
	}
	void WorldBase::CallOnActorsRemoved() {
		if (OnActorsRemoved)
			OnActorsRemoved();
	}
	bool WorldBase::Quit() const {
		return _quit;
	}
	void WorldBase::RefreshView(const sf::Vector2f& center) const {
		_parent->RefreshView(center);
	}
	std::optional<sf::Vector2f> WorldBase::GetMainCharacterPosition() const {
		if (auto character = _main_controller->GetMainCharacter(); character)
			return character->GetPosition();
		return {};
	}
	void WorldBase::ServiceInput(const Core::Controller::Key& key) {
		if (_main_controller)
			_main_controller->ServiceInput(key);
	}
	void WorldBase::InitWorld() {
		if (_initialized)
			throw std::runtime_error("Double initialization of world\n");
		try {
			if (_actor_manager and _main_controller) {
				_main_controller->InitMainCharacter();
				_main_controller->InitMainCharacterInputBindings();
				_actor_manager->RegisterMainActor(_main_controller->GetMainCharacter());
			}
			else {
				std::cerr << "WorldBase::InitWorld _actor_manager or _main_controller is empty\n";
			}
			CreateWorldBaseComponents();
			InitWorldBaseComponents();
			_initialized = true;
		}
		catch (std::exception& ex) {
			std::cerr << "WorldBase::InitWorld exception " << ex.what() << std::endl;
			_initialized = false;
		}
	}
	void WorldBase::InitWorldBaseComponents() {
		for (const auto& component : _world_components)
			component->InitComponent();
	}
	void WorldBase::EndWorld() {
		if (!_initialized)
			throw std::runtime_error("End uninitialized world\n");
		if (_actor_manager) {
			_actor_manager->Terminate();
			_actor_manager->Wait();
		}
		for (const auto& component : _world_components)
			component->EndComponent();
	}
}