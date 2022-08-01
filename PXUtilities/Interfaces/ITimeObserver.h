#pragma once
class ITimeObserver {
public:
	virtual void SecondPassed(unsigned int second) = 0;
	virtual void MinutePassed(unsigned int minute) = 0;
};