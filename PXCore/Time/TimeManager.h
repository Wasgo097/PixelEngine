#pragma once
#include <set>
#include "PXUtilities/Interfaces/ITimeObservable.h"
#include "PXUtilities/Interfaces/ITimeObserver.h"
#include "PXUtilities/Interfaces/ILoopingThread.h"
#include "PXUtilities/ThreadingResource.h"
#include "PXCore/Object/Actor.h"
namespace Core {
	class WorldBase;
}
namespace Core::Time {
	class TimeManager : public ITimeObservable, public ILoopingThread {
	public:
		TimeManager(float multiplier = 1.0);
		virtual ~TimeManager();

		// Inherited via ITimeObservable
		virtual void AttachToSeconds(ITimeObserver* item) override;
		virtual void AttachToMinutes(ITimeObserver* item) override;
		virtual void DetachFromSeconds(ITimeObserver* item) override;
		virtual void DetachFromMinutes(ITimeObserver* item) override;

		// Inherited via IThread
		virtual void Run()override;
		virtual void Terminate()override;
		virtual void Wait()override;

		void Multiplier(float value);
		float Multiplier()const;
	protected:
		virtual void NotifyForSecondPassed(unsigned int current_second) override;
		virtual void NotifyForMinutePassed(unsigned int current_minute) override;

		std::unique_ptr<std::thread> _thread;
		Utility::ThreadingResourceLight<std::set<ITimeObserver*>> _seconds;
		Utility::ThreadingResourceLight<std::set<ITimeObserver*>> _minutes;
		std::atomic<float> _multipler;
		std::atomic<unsigned int> _elapsed_seconds = 0;
		std::atomic<unsigned int> _elapsed_minutes = 0;
		bool _terminated = false;
	};
}
