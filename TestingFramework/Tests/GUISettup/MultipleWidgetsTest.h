#pragma once
#include "BaseTest.h"
#include <TGUI/TGUI.hpp>
namespace Test {
	class MultipleWidgetsTest :public BaseTest{
	public:
		virtual bool PrepareTest() override;
		virtual bool RunTest() override;
	protected:
		bool runExample(tgui::GuiBase& gui);

	};
}