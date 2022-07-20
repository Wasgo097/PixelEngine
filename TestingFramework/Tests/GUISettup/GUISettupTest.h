#pragma once
#include "BaseTest.h"
namespace Test {
	class GUISettupTest:public BaseTest{
	public:
		virtual bool PrepareTest() override;
		virtual bool RunTest() override;
	};
}