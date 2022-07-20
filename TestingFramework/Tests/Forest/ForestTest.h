#pragma once
#include "BaseTest.h"
#include "EngineForForestTest.h"
namespace Test {
	class ForestTest : public BaseTest{
	public:
		// Inherited via BaseTest
		virtual bool PrepareTest() override;
		virtual bool RunTest() override;
	protected:
		EngineForForestTest _engine;
	};
}
