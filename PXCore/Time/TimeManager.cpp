#include "TimeManager.h"
#include "PXUtilities/Interfaces/ITimeObserver.h"
#include "PXCore/World/WorldBase.h"
namespace Core::Time {
	TimeManager::TimeManager(Core::World::WorldBase* world, float multiplier) :
		_thread(std::make_unique<std::thread>(&TimeManager::Run, this)),
		Core::Object::Actor(world, Settings::ActorSettings(), Settings::TextureSettings()) {
		_multipler = multiplier;
	}
	void TimeManager::Multiplier(float value) {
		_multipler = value;
	}
	float TimeManager::Multiplier() const {
		return _multipler;
	}
	void TimeManager::Run() {
		auto second_point = std::chrono::high_resolution_clock::now();
		auto minutes_point = second_point;
		while (!_terminated) {
			auto now = std::chrono::high_resolution_clock::now();
			bool second_pass = std::chrono::duration_cast<std::chrono::milliseconds>(now - second_point).count() > static_cast<long long>(1000.f / _multipler);
			bool minute_pass = std::chrono::duration_cast<std::chrono::milliseconds>(now - minutes_point).count() > static_cast<long long>(60000.f / _multipler);
			if (second_pass) {
				NotifyForSecondPassed();
				second_point = now;
			}
			if (minute_pass) {
				NotifyForMinutePassed();
				minutes_point = now;
			}
		}
	}
	void TimeManager::Terminate() {
		_terminated = true;
	}
	void TimeManager::Wait() {
		if (_thread->joinable())
			_thread->join();
	}
	TimeManager::~TimeManager()
	{
		Terminate();
		Wait();
	}
	void TimeManager::AttachToSeconds(ITimeObserver* item) {
		if (item != nullptr) {
			std::lock_guard lock(_seconds.mtx);
			_seconds.rsc->insert(item);
		}
	}
	void TimeManager::AttachToMinutes(ITimeObserver* item) {
		if (item != nullptr) {
			std::lock_guard lock(_minutes.mtx);
			_minutes.rsc->insert(item);
		}
	}
	void TimeManager::DetachFromSeconds(ITimeObserver* item) {
		if (item != nullptr) {
			std::lock_guard lock(_seconds.mtx);
			_seconds.rsc->erase(item);
		}
	}
	void TimeManager::DetachFromMinutes(ITimeObserver* item) {
		if (item != nullptr) {
			std::lock_guard lock(_minutes.mtx);
			_minutes.rsc->erase(item);
		}
	}
	void TimeManager::NotifyForSecondPassed() {
		std::lock_guard lock(_seconds.mtx);
		for (auto& observator : *_seconds.rsc) {
			observator->SecondPassed();
		}
	}
	void TimeManager::NotifyForMinutePassed() {
		std::lock_guard lock(_minutes.mtx);
		for (auto& observator : *_minutes.rsc) {
			observator->MinutePassed();
		}
	}
}