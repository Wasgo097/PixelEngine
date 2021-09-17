#pragma once
namespace Time {
	class ITimeObserver {
		virtual void SecondPassed ()const = 0;
		virtual void MinutePassed ()const = 0;
	};
}