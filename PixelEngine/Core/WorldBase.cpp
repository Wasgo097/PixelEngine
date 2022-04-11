#include "Utility/CommonHeaders.h"
#include "WorldBase.h"
#include "ActorManager.h"
#include "Controller/ControllerBase.h"
#include "Engine.h"
namespace Core {
	WorldBase::WorldBase(const Settings::WorldSettings& worlsettings, Engine* parent) :_Parent(parrent),
		_worldsettings(worlsettings),_actormanager(std::make_unique<ActorManager>(worlsettings._buffersize, worlsettings._gcfrequentlevel, worlsettings._cycletomove)){
		if (_actormanager&&_maincontroller){
			_actormanager->RegisterMainActor(_maincontroller->GetMainCharacter());
		}
	}
	WorldBase::~WorldBase(){
		if (_actormanager) {
			_actormanager->Wait();
			_actormanager->Terminate();
		}
	}
	void WorldBase::Draw(sf::RenderWindow& window) {
		if (_actormanager)
			_actormanager->Draw(window);
	}
	void WorldBase::Update(float delta){
		if (_actormanager)
			_actormanager->Update(delta);
	}
	void WorldBase::SetParnet(Engine* parrent){
		if (_Parent != nullptr)
			printf("WARNIGN!! WorldBase::SetParrnet change parrent when parrent is setted\n");
		_Parent = parrent;
	}
	bool WorldBase::Quit() const
	{
		return _quit;
	}
	bool WorldBase::Initialized() const
	{
		return false;
	}
	void WorldBase::ServiceInput(sf::Event event){
		_maincontroller->ServiceInput(event);
	}
	void WorldBase::InitWorld()	{
		if (_Initialized)
			std::runtime_error("Double initialization of world\n");
		_Initialized = true;
	}
	void WorldBase::EndWorld(){
		if (!_Initialized)
			std::runtime_error("End uninitialized world\n");
	}
}