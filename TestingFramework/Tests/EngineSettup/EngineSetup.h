#pragma once
#include "BaseTest.h"
#include "PXCore/Engine.h"
namespace Test {
	class EngineSetup :public BaseTest{
	public:
		// Inherited via BaseTest
		virtual void PrepareTest() override;
		virtual bool RunTest() override;
	protected:
		Core::Engine _engine;
	};
}