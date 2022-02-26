#pragma once
#include "BaseTest.h"
namespace Test {
	class EngineSettup :public BaseTest{
	public:
		EngineSettup() {

		}
	public:
		// Inherited via BaseTest
		virtual void PrepareTest() override;
		virtual bool RunTest() override;
	};
}