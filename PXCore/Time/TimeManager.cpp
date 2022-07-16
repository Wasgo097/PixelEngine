#include "TimeManager.h"
#include "PXUtilities/Interfaces/ITimeObserver.h"
#include "PXCore/World/WorldBase.h"
namespace Core::Time{
	TimeManager::TimeManager(Core::World::WorldBase* world, float multiplier) :
		_thread(std::make_unique<std::thread>(&TimeManager::Run, this)),
		Core::Object::Actor(world,Settings::ActorSettings(),Settings::TextureSettings()){
		_multipler = multiplier;
	}
	void TimeManager::Multiplier(float value){
		_multipler = value;
	}
	float TimeManager::Multiplier() const{
		return _multipler;
	}
	void TimeManager::Run(){
		auto _seconds_point = std::chrono::high_resolution_clock::now();
		auto _minutes_point = _seconds_point;
		while(!_terminated){
			auto now = std::chrono::high_resolution_clock::now();
			bool second_pass = false;
			bool minute_pass = false;
			second_pass = std::chrono::duration_cast<std::chrono::milliseconds>(now - _seconds_point).count() > (1000 / _multipler);
			minute_pass = std::chrono::duration_cast<std::chrono::milliseconds>(now - _seconds_point).count() > (60000 / _multipler);
			if(second_pass){
				NotifyForSecondPassed();
				_seconds_point = now;
			}
			if(minute_pass){
				NotifyForMinutePassed();
				_minutes_point = now;
			}
		}
	}
	void TimeManager::Terminate(){
		_terminated = true;
	}
	void TimeManager::Wait(){
		if(_thread->joinable())
			_thread->join();
	}
	void TimeManager::AttachToSeconds(ITimeObserver * item){
		if(item != nullptr){
			std::lock_guard lock(_seconds.mtx);
			_seconds.rsc->insert(item);
		}
	}
	void TimeManager::AttachToMinutes(ITimeObserver * item){
		if(item){
			std::lock_guard lock(_minutes.mtx);
			_minutes.rsc->insert(item);
		}
	}
	void TimeManager::DetachFromSeconds(ITimeObserver * item){
		if(item){
			std::lock_guard lock(_seconds.mtx);
			_seconds.rsc->erase(item);
		}
	}
	void TimeManager::DetachFromMinutes(ITimeObserver * item){
		if(item){
			std::lock_guard lock(_minutes.mtx);
			_minutes.rsc->erase(item);
		}
	}
	void TimeManager::NotifyForSecondPassed(){
		std::lock_guard lock(_seconds.mtx);
		for(auto & observator : *_seconds.rsc){
			observator->SecondPassed();
		}
	}
	void TimeManager::NotifyForMinutePassed(){
		std::lock_guard lock(this->_minutes.mtx);
		for(auto & observator : *_minutes.rsc){
			observator->MinutePassed();
		}
	}
}