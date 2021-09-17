#pragma once
#include "ITimeObservable.h"
#include "CommonHeaders.h"
#include "Utility/CommonStructures.h"
#include "Time/ITimeObserver.h"
namespace Time {
	class TimeManager : public ITimeObservable {
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
		~TimeManager();
		TimeManager(const TimeManager&) = delete;
		TimeManager& operator=(const TimeManager&) = delete;
		TimeManager(TimeManager&& src);
		TimeManager& operator=(TimeManager&&src);
		void Run();
		void Terminate ();
		void Wait ();
	protected:
		std::unique_ptr<std::thread> _thr;
		Utility::ThreadingResourceLight<std::set<ITimeObserver *>> _seconds;
		Utility::ThreadingResourceLight<std::set<ITimeObserver *>> _minutes;
		bool _terminated = false;
	};
}
