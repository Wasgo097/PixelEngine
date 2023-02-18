#pragma once
#include "BaseTest.h"
#include <TGUI/TGUI.hpp>
namespace Test {
	class PopUp :public BaseTest {
	public:
		PopUp(const ArgumentParser& parser);
		virtual bool PrepareTest() override;
		virtual bool RunTest() override;
	protected:
		// Called when a right click is detected while popup menu isn't shown
		void RightClickCallback(tgui::GuiBase& gui, tgui::Vector2f position);
		void PopupMenuCallback(tgui::String item);
		tgui::ListBox::Ptr _popupMenu{ nullptr };
	};
}