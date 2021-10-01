#pragma once
namespace Time {
	class ITimeObserver {
	public:
		virtual void SecondPassed () = 0;
		virtual void MinutePassed () = 0;
	};
}