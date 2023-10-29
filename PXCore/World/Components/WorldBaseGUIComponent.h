#pragma once
#include <TGUI/TGUI.hpp>
namespace Core::World {
	class WorldBaseGUI;
}
namespace Core::World::Component {
	class WorldBaseGUIComponent {
	public:
		WorldBaseGUIComponent(WorldBaseGUI* parent, tgui::Gui* gui,std::optional<tgui::Theme> theme=std::nullopt);
		virtual void Tick(float delta_time) = 0;
		virtual void Draw() = 0;
		virtual void InitComponent() = 0;
		virtual void EndComponent() = 0;
		bool TickFlag()const;
		void SetTickFlag(bool flag);
	private:
		bool _tick = false;
	protected:
		WorldBaseGUI* _parent;
		std::optional<tgui::Theme> _theme;
		tgui::Gui* _gui;
		bool _initialized = true;
	};
}
