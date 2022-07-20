#pragma once
class ITimeObserver {
public:
	virtual void SecondPassed() = 0;
	virtual void MinutePassed() = 0;
};