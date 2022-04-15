#pragma once
#include "BaseTest.h"
#include "Core/Engine/Engine.h"
namespace Test {
	class ActorAnimationTest : public BaseTest
	{
	public:
		// Inherited via BaseTest
		virtual void PrepareTest() override;
		virtual bool RunTest() override;
	protected:
		Core::Engine _engine;
	};
}
