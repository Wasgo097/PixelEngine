#include "Time/TimeManager.h"
#include "Time/ITimeObserver.h"
namespace Time {

	TimeManager::TimeManager(){
		_thr = std::make_unique<std::thread>(&TimeManager::Run, this);
	}
	TimeManager::~TimeManager(){
		Terminate();
		Wait();
	}
	TimeManager::TimeManager(TimeManager && src) :
		_thr(std::move(src._thr)),
		_seconds(std::move(src._seconds)),
		_minutes(std::move(src._minutes)),
		_terminated (src._terminated)
	{}
	TimeManager & TimeManager::operator=(TimeManager && src){
		_thr = std::move(src._thr);
		_seconds = std::move(src._seconds);
		_minutes = std::move(src._minutes);
		_terminated = src._terminated;
		return *this;
	}
	void TimeManager::Run(){
		auto _seconds_point = std::chrono::high_resolution_clock::now();
		auto _minutes_point = _seconds_point;
		while(!_terminated){
			auto now = std::chrono::high_resolution_clock::now();
			if(std::chrono::duration_cast<std::chrono::milliseconds>(now - _seconds_point).count() > 1000){
				NotifyForSecondPassed();
				_seconds_point = now;
			}
			if(std::chrono::duration_cast<std::chrono::milliseconds>(now - _minutes_point).count() > 60000){
				NotifyForMinutePassed();
				_minutes_point = now;
			}
		}
	}
	void TimeManager::Terminate () {
		_terminated = true;
	}
	void TimeManager::Wait () {
		if(_thr->joinable())
			_thr->join();
	}
	void TimeManager::AttachToSeconds(ITimeObserver * item){
		if(item!=nullptr){
			std::lock_guard lock(_seconds._mtx);
			_seconds._rsc.insert(item);
		}
	}
	void TimeManager::AttachToMinutes(ITimeObserver * item){
		if(item){
			std::lock_guard lock(_minutes._mtx);
			_minutes._rsc.insert(item);
		}
	}
	void TimeManager::DetachFromSeconds(ITimeObserver * item){
		if(item){
			std::lock_guard lock(_seconds._mtx);
			_seconds._rsc.erase(item);
		}
	}
	void TimeManager::DetachFromMinutes(ITimeObserver * item){
		if(item){
			std::lock_guard lock(_minutes._mtx);
			_minutes._rsc.erase(item);
		}
	}
	void TimeManager::NotifyForSecondPassed() {
		std::lock_guard lock(_seconds._mtx);
		for(auto & observator : _seconds._rsc){
			observator->SecondPassed();
		}
	}
	void TimeManager::NotifyForMinutePassed() {
		std::lock_guard lock(this->_minutes._mtx);
		for(auto & observator : _minutes._rsc){
			observator->MinutePassed();
		}
	}
}