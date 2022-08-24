#pragma once
#include "BaseTest.h"
namespace Test {
	class ParticleTest : public BaseTest {
	public:
		ParticleTest(const ArgumentParser& parser);
		virtual bool PrepareTest();
		virtual bool RunTest();
	};
}