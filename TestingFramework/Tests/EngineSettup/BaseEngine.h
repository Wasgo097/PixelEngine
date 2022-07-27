#pragma once
#include "PXCore/Engine.h"
namespace Test {
	class BaseEngine :public Core::Engine {
	public:
		// Inherited via Engine
		virtual void InitEngine() override;
	};
}