#pragma once
#include"CommonHeaders.h"
namespace Time {
	class ITimeObserver;
	class ITimeObservable {
	public:
		virtual void AttachToSeconds (ITimeObserver * item) = 0;
		virtual void AttachToMinutes (ITimeObserver * item) = 0;
		virtual void DetachFromSeconds (ITimeObserver * item) = 0;
		virtual void DetachFromMinutes (ITimeObserver * item) = 0;
		virtual void NotifyForSecondPassed ()const = 0;
		virtual void NotifyForMinutePassed ()const = 0;
	};
}

