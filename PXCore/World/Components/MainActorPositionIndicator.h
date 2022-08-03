#pragma once
#include "WorldBaseGUIComponent.h"
#include "PXCore/Object/ControlledActor.h"
namespace Core::World::Component {
	class MainActorPositionIndicator :public WorldBaseGUIComponent {
	public:
		MainActorPositionIndicator(WorldBaseGUI* parent, tgui::Gui* gui, std::optional<tgui::Theme> theme = std::nullopt, std::shared_ptr<Core::Object::ControlledActor> tracked_actor = {});
		virtual void InitComponent();
		virtual void Tick(float delta_time) override;
		virtual void Draw() override;
	protected:
		std::weak_ptr<Core::Object::ControlledActor> _actor;
		tgui::Label::Ptr _position_label;
	};
}