#pragma once
#include "WorldBaseGUIComponent.h"
namespace Core::World::Component {
	class ActorsCounter :public WorldBaseGUIComponent {
	public:
		ActorsCounter(Core::World::WorldBaseGUI* parent, tgui::Gui* gui, std::optional<tgui::Theme> theme = std::nullopt);
		virtual void Tick(float delta_time)override {};
		virtual void Draw()override;
		virtual void InitComponent()override;
		virtual void EndComponent() override {}
		void SetCountOfActors(size_t new_count);
	protected:
		tgui::Label::Ptr _counter;
	};
}