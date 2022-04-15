#include "EngineForAnimationTest.h"
#include "WorldForAnimationTest.h"
namespace Test {
	void EngineForAnimationTest::InitEngine()
	{
		PushWorld(std::make_unique<WorldForAnimationTest>(_worldsettings, this));
		_worlds.top()->InitWorld();
	}
}