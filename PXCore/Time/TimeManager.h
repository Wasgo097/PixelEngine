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
using namespace Time;
namespace Core::Time {
	class TimeManager : public ITimeObservable, ILoopingThread, Core::Object::Actor {
	public:
		TimeManager(Core::World::WorldBase* world = nullptr, float multiplier = 1.0);
		TimeManager(const TimeManager&) = delete;
		TimeManager& operator=(const TimeManager&) = delete;
		TimeManager(TimeManager&& src) = delete;
		TimeManager& operator=(TimeManager&& src) = delete;
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
		virtual void NotifyForSecondPassed()  override;
		virtual void NotifyForMinutePassed()  override;

		std::unique_ptr<std::thread> _thread;
		Utility::ThreadingResourceLight<std::set<ITimeObserver*>> _seconds;
		Utility::ThreadingResourceLight<std::set<ITimeObserver*>> _minutes;
		std::atomic<float> _multipler;
		bool _terminated = false;
	};
}
