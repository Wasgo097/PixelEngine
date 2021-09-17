#include "Time/TimeManager.h"
#include "Time/ITimeObserver.h"
namespace Time {

	TimeManager::TimeManager(){
		_thr = std::make_unique<std::thread>(&TimeManager::Run, this);
	}
	TimeManager::~TimeManager(){
		Wait();
	}
	TimeManager::TimeManager(TimeManager && src):_thr(std::move(src._thr)),
		_seconds(std::move(src._seconds)),_minutes(std::move(src._minutes)){}
	TimeManager & TimeManager::operator=(TimeManager && src){
		// TODO: insert return statement here
		return *this;
	}
	void TimeManager::Run(){
		
	}
	void TimeManager::Terminate () {
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
		}
	}
	void TimeManager::NotifyForSecondPassed() const{}
	void TimeManager::NotifyForMinutePassed() const{}
}