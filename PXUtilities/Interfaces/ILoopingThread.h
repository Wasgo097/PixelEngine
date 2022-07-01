#pragma once
class ILoopingThread {
public:
	virtual void Run() = 0;
	virtual void Wait() = 0;
	virtual void Terminate() = 0;
	virtual ~ILoopingThread() = default;
};