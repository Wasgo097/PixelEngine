#include "WorldBase.h"
#include <iostream>
#include "ActorsManager.h"
#include "Controller/ControllerBase.h"
#include "Engine.h"
namespace Core::World {
	WorldBase::WorldBase(const Settings::WorldSettings& world_settings, Engine* parent) :_parent(parent),
		_world_settings(world_settings), _actor_manager(std::make_unique<ActorsManager>(world_settings.buffer_size, world_settings.gc_delay)) {
	}
	void WorldBase::Draw(sf::RenderWindow& window) {
		if (!_initialized)
			throw std::runtime_error("Draw uninitialized world");
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
	}
	void WorldBase::CheckCollisionOnMove(Core::Object::Actor* actor) {
	}
	bool WorldBase::Quit() const {
		return _quit;
	}

	bool WorldBase::Initialized() const {
		return _initialized;
	}
	void WorldBase::ServiceInput(const Core::Controller::Key& key) {
		if (_main_controller)
			_main_controller->ServiceInput(key);
	}
	void WorldBase::InitWorld() {
		if (_initialized)
			throw std::runtime_error("Double initialization of world\n");
		if (_actor_manager && _main_controller) {
			_main_controller->InitMainCharacter();
			_main_controller->InitMainCharacterInputBindings();
			_actor_manager->RegisterMainActor(_main_controller->GetMainCharacter());
			_initialized = true;
		}
	}
	void WorldBase::EndWorld() {
		if (!_initialized)
			throw std::runtime_error("End uninitialized world\n");
		if (_actor_manager) {
			_actor_manager->Terminate();
			_actor_manager->Wait();
		}
	}
}