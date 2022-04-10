#include "Utility/CommonHeaders.h"
#include "WorldBase.h"
#include "ActorManager.h"
#include "Controller/ControllerBase.h"
#include "Engine.h"
namespace Core {
	WorldBase::WorldBase(const Settings::WorldSettings& worlsettings, Engine* parrent) :_parrent(parrent),
		_worldsettings(worlsettings),_actormanager(std::make_unique<ActorManager>(worlsettings._buffersize, worlsettings._gcfrequentlevel, worlsettings._cycletomove)){
		InitWorld();
		if (_actormanager&&_maincontroller){
			_actormanager->RegisterMainActor(_maincontroller->GetMainCharacter());
		}
	}
	WorldBase::~WorldBase(){
		EndWorld();
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
		CheckQuit();
		if (_actormanager)
			_actormanager->Update(delta);
	}
	void WorldBase::SetParrnet(Engine* parrent){
		if (_parrent != nullptr)
			printf("WARNIGN!! WorldBase::SetParrnet change parrent when parrent is setted");
		_parrent = parrent;
	}
	bool WorldBase::Quit() const
	{
		return _quit;
	}
	void WorldBase::ServiceInput(sf::Event event){
		_maincontroller->ServiceInput(event);
	}
}