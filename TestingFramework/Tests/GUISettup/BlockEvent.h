#pragma once
#include "BaseTest.h"
#include <TGUI/TGUI.hpp>
namespace Test {
	class BlockEvent :public BaseTest {
	public:
		BlockEvent(const ArgumentParser& parser);
		virtual bool PrepareTest() override;
		virtual bool RunTest() override;
	protected:
		bool RunExample(tgui::GuiBase& gui);
		void OpenWindow();
		void CloseWindow();
		tgui::GuiBase* _guiPtr{ nullptr };
	};
}