#pragma once
namespace Time {
	class ITimeObserver {
	public:
		virtual void SecondPassed ()const = 0;
		virtual void MinutePassed ()const = 0;
	};
}