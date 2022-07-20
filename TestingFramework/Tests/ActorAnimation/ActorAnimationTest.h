#pragma once
#include "BaseTest.h"
#include "EngineForAnimationTest.h"
namespace Test {
	class ActorAnimationTest : public BaseTest{
	public:
		// Inherited via BaseTest
		virtual bool PrepareTest() override;
		virtual bool RunTest() override;
	protected:
		EngineForAnimationTest _engine;
	};
}
