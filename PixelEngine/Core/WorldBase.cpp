#include "Utility/CommonHeaders.h"
#include "WorldBase.h"
#include "ActorManager.h"
#include "Controller/ControllerBase.h"
#include "Engine.h"
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
		_parrent = parrent;
	}
	bool WorldBase::Quit() const
	{
		return _quit;
	}
	void WorldBase::ServiceInput(sf::Event event){
		_maincontroller->ServiceInput(event);
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