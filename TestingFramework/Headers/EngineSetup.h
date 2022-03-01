#pragma once
#include "BaseTest.h"
#include <Core/Engine.h>
namespace Test {
	class EngineSetup :public BaseTest{
	public:
		EngineSetup();
	public:
		// Inherited via BaseTest
		virtual void PrepareTest() override;
		virtual bool RunTest() override;
	protected:
		Core::Engine _engine;
	};
}