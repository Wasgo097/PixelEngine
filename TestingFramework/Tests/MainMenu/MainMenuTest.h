#pragma once
#include "BaseTest.h"
namespace Test {
	class MainMenuTest :public BaseTest {
		// Inherited via BaseTest
		virtual bool PrepareTest() override;
		virtual bool RunTest() override;
	};
}