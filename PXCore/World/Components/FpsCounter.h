#pragma once
#include "WorldBaseGUIComponent.h"
namespace Core::World::Component {
	class FpsCounter :public WorldBaseGUIComponent {
	public:
		FpsCounter(WorldBaseGUI* parent, tgui::Gui* gui, std::optional<tgui::Theme> theme = std::nullopt);
		virtual void Tick(float delta_time) override;
		virtual void Draw()override;
		virtual void InitComponent()override;
	protected:
		tgui::Label::Ptr _fps_label;
	};
}