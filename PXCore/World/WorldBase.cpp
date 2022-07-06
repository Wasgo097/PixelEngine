#include "WorldBase.h"
#include <iostream>
#include "ActorsManager.h"
#include "Controller/ControllerBase.h"
#include "Engine.h"
namespace Core::World {
	WorldBase::WorldBase(const Settings::WorldSettings& world_settings, Engine* parent) :_parent(parent),
		_world_settings(world_settings),_actor_manager(std::make_unique<ActorsManager>(world_settings.buffer_size, world_settings.gc_frequent_level, world_settings.cycle_to_move)){
	}
	void WorldBase::Draw(sf::RenderWindow& window) {
		if (!_initialized)
			std::cout << "Draw uninitialized world\n";
		if (_actor_manager)
			_actor_manager->Draw(window);
	}
	void WorldBase::Update(float delta){
		if (!_initialized)
			std::cout << "Update uninitialized world\n";
		//if (delta > 0.2)
			std::cout << "Tick time above save value " << delta << "\n";
		if (_actor_manager)
			_actor_manager->Update(delta);
	}
	void WorldBase::SetParnet(Engine* parent){
		if (_parent != nullptr)
			printf("WARNIGN!! WorldBase::SetParrnet change parrent when parrent is setted\n");
		_parent = parent;
	}
	bool WorldBase::Quit() const
	{
		return _quit;
	}
	bool WorldBase::Initialized() const
	{
		return _initialized;
	}
	void WorldBase::ServiceInput(sf::Event action){
		if(_main_controller)
			_main_controller->ServiceInput(action);
	}
	void WorldBase::InitWorld()	{
		if (_initialized)
			throw std::runtime_error("Double initialization of world\n");
		_main_controller->InitMainCharacterInputBindings();
		_main_controller->InitMainCharacter();
		if (_actor_manager && _main_controller)
			_actor_manager->RegisterMainActor(_main_controller->GetMainCharacter());
		_initialized = true;
	}
	void WorldBase::EndWorld(){
		if (!_initialized)
			throw std::runtime_error("End uninitialized world\n");
		if (_actor_manager) {
			_actor_manager->Terminate();
			_actor_manager->Wait();
		}
	}
}