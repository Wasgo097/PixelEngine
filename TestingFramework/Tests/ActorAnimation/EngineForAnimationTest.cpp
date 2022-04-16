#include "EngineForAnimationTest.h"
#include "WorldForAnimationTest.h"
namespace Test {
	void EngineForAnimationTest::InitEngine(){
		PushWorldToQueue(std::make_unique<WorldForAnimationTest>(_worldsettings, this));
		_WorldsQueue.top()->InitWorld();
	}
}