#pragma once
#include "BaseTest.h"
#include <TGUI/TGUI.hpp>
namespace Test {
	class ScrollablePanel :public BaseTest {
	public:
		ScrollablePanel(const ArgumentParser& parser);
		virtual bool PrepareTest() override;
		virtual bool RunTest() override;
	protected:
		bool RunExample(tgui::GuiBase& gui);
	};
}