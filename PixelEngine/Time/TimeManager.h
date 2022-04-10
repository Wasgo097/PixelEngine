#pragma once
#include "ITimeObservable.h"
#include "Types/ILoopingThread.h"
#include "Objects/Actor.h"
#include "Utility/ThreadingResource.h"
namespace Core{
	class WorldBase;
}
namespace Time {
	class ITimeObserver;
	class TimeManager : public ITimeObservable,Types::ILoopingThread,Core::Actor {
	public:
		// Inherited via ITimeObservable
		virtual void AttachToSeconds(ITimeObserver * item) override;
		virtual void AttachToMinutes(ITimeObserver * item) override;
		virtual void DetachFromSeconds(ITimeObserver * item) override;
		virtual void DetachFromMinutes(ITimeObserver * item) override;
		virtual void NotifyForSecondPassed()  override;
		virtual void NotifyForMinutePassed()  override;
	public:
		TimeManager(Core::WorldBase* world,float multiplier = 1.0);
		TimeManager(const TimeManager&) = delete;
		TimeManager& operator=(const TimeManager&) = delete;
		TimeManager(TimeManager&& src) = delete;
		TimeManager& operator=(TimeManager&&src)=delete;
		void Multiplier(float value);
		float Multiplier()const;
	public:
		// Inherited via IThread
		virtual void Run()override;
		virtual void Terminate ()override;
		virtual void Wait ()override;
	protected:
		std::unique_ptr<std::thread> _thread;
		Utility::ThreadingResourceLight<std::set<ITimeObserver *>> _seconds;
		Utility::ThreadingResourceLight<std::set<ITimeObserver *>> _minutes;
		std::atomic<float> _multipler;
		bool _terminated = false;
	};
}
