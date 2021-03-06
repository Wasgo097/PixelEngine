#pragma once
#include "BaseTest.h"
#include "BaseEngine.h"
namespace Test {
	class EngineSetupTest :public BaseTest{
	public:
		// Inherited via BaseTest
		virtual bool PrepareTest() override;
		virtual bool RunTest() override;
	protected:
		BaseEngine _engine;
	};
}