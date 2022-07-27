#pragma once
#include <TGUI/TGUI.hpp>
namespace Core::World {
	class BaseWorldGUI;
}
namespace Core::World::Component {
	class WorldBaseGUIComponent {
	public:
		WorldBaseGUIComponent(BaseWorldGUI* parent, tgui::Gui* gui);
		virtual void Tick(float delta_time) = 0;
		virtual void InitComponent() {};
		virtual void EndComponent() {};
		bool TickFlag()const;
		void SetTickFlag(bool flag);
	private:
		bool _tick = false;
	protected:
		BaseWorldGUI* _parent;
		tgui::Gui* _gui;
	};
}
