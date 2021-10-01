#pragma once
namespace Types{
	class ILoopingThread{
	public:
		virtual void Run() = 0;
		virtual void Wait() = 0;
		virtual void Terminate() = 0;
	};
}