#pragma once
#include "PXCore/Engine.h"
namespace Test {
	class MainMenuEngine:public Core::Engine{
	public:
		void ApplyWindowSettings(const Settings::WindowSettingsDTO& new_settings);
	protected:
		// Inherited via Engine
		virtual void InitEngine() override;
	};
}
