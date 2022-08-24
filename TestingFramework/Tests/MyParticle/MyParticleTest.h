#pragma once
#include "BaseTest.h"
namespace Test {
	class MyParticleTest :public BaseTest {
	public:
		MyParticleTest(const ArgumentParser& parser) :BaseTest{ parser } {}
		virtual bool PrepareTest()override;
		virtual bool RunTest()override;
	};
}