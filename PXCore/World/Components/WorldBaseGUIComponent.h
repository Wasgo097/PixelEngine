#pragma once
#include <TGUI/TGUI.hpp>
namespace Core::World {
	class WorldBaseGUI;
}
namespace Core::World::Component {
	class WorldBaseGUIComponent {
	public:
		WorldBaseGUIComponent(WorldBaseGUI* parent, tgui::Gui* gui);
		virtual void Tick(float delta_time) = 0;
		virtual void InitComponent() {};
		virtual void EndComponent() {};
		bool TickFlag()const;
		void SetTickFlag(bool flag);
	private:
		bool _tick = false;
	protected:
		WorldBaseGUI* _parent;
		tgui::Gui* _gui;
	};
}
