#pragma once
#include "WorldBaseGUIComponent.h"
namespace Core::World::Component {
	class FpsCounter :public WorldBaseGUIComponent {
	public:
		FpsCounter(BaseWorldGUI* parent, tgui::Gui* gui);
		// Inherited via WorldBaseGUIComponent
		virtual void InitComponent()override;
		virtual void Tick(float delta_time) override;
	protected:
		tgui::Label::Ptr _fps_label;
	};
}