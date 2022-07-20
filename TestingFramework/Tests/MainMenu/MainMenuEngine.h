#pragma once
#include "PXCore/Engine.h"
namespace Test {
	class MainMenuEngine:public Core::Engine{
	protected:
		// Inherited via Engine
		virtual void InitEngine() override;
	};
}
