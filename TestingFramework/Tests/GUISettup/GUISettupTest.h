#pragma once
#include "BaseTest.h"
namespace Test {
	class GUISettupTest:public BaseTest{
	public:
		virtual void PrepareTest() override;
		virtual bool RunTest() override;
	};
}