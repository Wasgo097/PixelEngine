#pragma once
#include "BaseTest.h"
#include "MainMenuEngine.h"
namespace Test {
	class MainMenuTest :public BaseTest {
	public:
		// Inherited via BaseTest
		virtual bool PrepareTest() override;
		virtual bool RunTest() override;
	protected:
		MainMenuEngine _engine;
	};
}