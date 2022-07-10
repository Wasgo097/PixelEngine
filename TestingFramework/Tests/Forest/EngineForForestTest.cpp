#include "EngineForForestTest.h"
#include "WorldForForestTest.h"
namespace Test {
	void EngineForForestTest::InitEngine(){
		PushWorldToQueue(std::make_unique<WorldForForestTest>(_world_settings, this));
	}
}