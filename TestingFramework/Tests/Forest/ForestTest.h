#pragma once
#include "BaseTest.h"
#include "EngineForForestTest.h"
namespace Test {
	class ForestTest : public BaseTest {
	public:
		ForestTest(const ArgumentParser& parser);
		// Inherited via BaseTest
		virtual bool PrepareTest() override;
		virtual bool RunTest() override;
	protected:
		EngineForForestTest _engine;
	};
}
