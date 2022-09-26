#pragma once
#include "BaseTest.h"
namespace Test {
	class Particle2Test :public BaseTest {
	public:
		Particle2Test(const ArgumentParser& parser);
		// Inherited via BaseTest
		virtual bool PrepareTest() override;
		virtual bool RunTest() override;
	};
}