#pragma once
namespace Test{
	class BaseTest{
	public:
		virtual void PrepareTest() = 0;
		virtual bool RunTest() = 0;
	};
}