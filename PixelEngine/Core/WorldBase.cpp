#include "Utility/CommonHeaders.h"
#include "WorldBase.h"
#include "ActorManager.h"
#include "Controller/ControllerBase.h"
namespace Core {
	WorldBase::WorldBase(const Settings::WorldSettings& worlsettings) :
		_worldsettings(worlsettings),_actormanager(std::make_unique<ActorManager>(worlsettings._buffersize, worlsettings._gcfrequentlevel, worlsettings._cycletomove)){
		InitWorld();
		if (_actormanager&&_maincontroller){
			_actormanager->RegisterMainActor(_maincontroller->GetMainCharacter());
		}
	}
	WorldBase::~WorldBase(){
		EndWorld();
	}
	void WorldBase::Draw(sf::RenderWindow& window) {
		//todo: draw whole world
		if (_actormanager)
			_actormanager->Draw(window);
	}
	void WorldBase::Update(float delta){
		CheckQuit();
		if (_actormanager)
			_actormanager->Update(delta);
	}
	void WorldBase::TermianateActorManager(){
		if (_actormanager)
			_actormanager->Terminate();
	}
	void WorldBase::WaitOnActorManager(){
		if (_actormanager)
			_actormanager->Wait();
	}
}