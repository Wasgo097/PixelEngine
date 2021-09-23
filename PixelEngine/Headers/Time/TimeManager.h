#pragma once
#include "ITimeObservable.h"
#include "CommonHeaders.h"
#include "Utility/CommonStructures.h"
#include "Time/ITimeObserver.h"
#include "Types/ILoopingThread.h"
namespace Time {
	class TimeManager : public ITimeObservable,Types::ILoopingThread {
	public:
		// Inherited via ITimeObservable
		virtual void AttachToSeconds(ITimeObserver * item) override;
		virtual void AttachToMinutes(ITimeObserver * item) override;
		virtual void DetachFromSeconds(ITimeObserver * item) override;
		virtual void DetachFromMinutes(ITimeObserver * item) override;
		virtual void NotifyForSecondPassed()  override;
		virtual void NotifyForMinutePassed()  override;
	public:
		TimeManager();
		virtual ~TimeManager();
		TimeManager(const TimeManager&) = delete;
		TimeManager& operator=(const TimeManager&) = delete;
		TimeManager(TimeManager&& src);
		TimeManager& operator=(TimeManager&&src);
	public:
		// Inherited via IThread
		virtual void Run()override;
		virtual void Terminate ()override;
		virtual void Wait ()override;
	protected:
		std::unique_ptr<std::thread> _thread;
		Utility::ThreadingResourceLight<std::set<ITimeObserver *>> _seconds;
		Utility::ThreadingResourceLight<std::set<ITimeObserver *>> _minutes;
		bool _terminated = false;
	};
}
