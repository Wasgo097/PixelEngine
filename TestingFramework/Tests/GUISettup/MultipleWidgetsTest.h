#pragma once
#include "BaseTest.h"
#include <TGUI/TGUI.hpp>
namespace Test {
	class MultipleWidgetsTest :public BaseTest {
	public:
		MultipleWidgetsTest(const ArgumentParser& parser);
		virtual bool PrepareTest() override;
		virtual bool RunTest() override;
	protected:
		bool RunExample(tgui::GuiBase& gui);
	};
}