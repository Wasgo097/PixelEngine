#pragma once
class ITimeObserver;
class ITimeObservable {
public:
	virtual void AttachToSeconds(ITimeObserver* item) = 0;
	virtual void AttachToMinutes(ITimeObserver* item) = 0;
	virtual void DetachFromSeconds(ITimeObserver* item) = 0;
	virtual void DetachFromMinutes(ITimeObserver* item) = 0;
protected:
	virtual void NotifyForSecondPassed() = 0;
	virtual void NotifyForMinutePassed() = 0;
};