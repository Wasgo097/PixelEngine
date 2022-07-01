#include "Utility/CommonHeaders.h"
#include "TimeManager.h"
#include "Interfaces/ITimeObserver.h"
#include "Core/World/WorldBase.h"
namespace Time{
	TimeManager::TimeManager(Core::WorldBase* world, float multiplier) :
		_thread(std::make_unique<std::thread>(&TimeManager::Run, this)),
		Core::Actor(world,Settings::ActorSettings(),Settings::TextureSettings()){
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
			std::lock_guard lock(_seconds.Mtx);
			_seconds.Rsc.insert(item);
		}
	}
	void TimeManager::AttachToMinutes(ITimeObserver * item){
		if(item){
			std::lock_guard lock(_minutes.Mtx);
			_minutes.Rsc.insert(item);
		}
	}
	void TimeManager::DetachFromSeconds(ITimeObserver * item){
		if(item){
			std::lock_guard lock(_seconds.Mtx);
			_seconds.Rsc.erase(item);
		}
	}
	void TimeManager::DetachFromMinutes(ITimeObserver * item){
		if(item){
			std::lock_guard lock(_minutes.Mtx);
			_minutes.Rsc.erase(item);
		}
	}
	void TimeManager::NotifyForSecondPassed(){
		std::lock_guard lock(_seconds.Mtx);
		for(auto & observator : _seconds.Rsc){
			observator->SecondPassed();
		}
	}
	void TimeManager::NotifyForMinutePassed(){
		std::lock_guard lock(this->_minutes.Mtx);
		for(auto & observator : _minutes.Rsc){
			observator->MinutePassed();
		}
	}
}