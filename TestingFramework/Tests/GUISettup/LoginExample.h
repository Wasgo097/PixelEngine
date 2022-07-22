#pragma once
#include "BaseTest.h"
#include <TGUI/TGUI.hpp>
namespace Test {
	class LoginExample :public BaseTest {
	public:
		virtual bool PrepareTest() override;
		virtual bool RunTest() override;
	protected:
		void login(tgui::EditBox::Ptr username, tgui::EditBox::Ptr password);
		void updateTextSize(tgui::GuiBase& gui);
		bool loadWidgets(tgui::GuiBase& gui);
		bool runExample(tgui::GuiBase& gui);
	};
}