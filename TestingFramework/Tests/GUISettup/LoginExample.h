#pragma once
#include "BaseTest.h"
#include <TGUI/TGUI.hpp>
namespace Test {
	class LoginExample :public BaseTest {
	public:
		LoginExample(const ArgumentParser& parser);
		virtual bool PrepareTest() override;
		virtual bool RunTest() override;
	protected:
		void Login(tgui::EditBox::Ptr username, tgui::EditBox::Ptr password);
		void UpdateTextSize(tgui::GuiBase& gui);
		bool LoadWidgets(tgui::GuiBase& gui);
		bool RunExample(tgui::GuiBase& gui);
	};
}