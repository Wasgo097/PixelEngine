#include "WorldBaseGUIComponent.h"
namespace Core::World::Component {
	WorldBaseGUIComponent::WorldBaseGUIComponent(WorldBaseGUI* parent, tgui::Gui* gui, std::optional<tgui::Theme> theme) :_parent{ parent }, _theme{ theme }, _gui{ gui }	{
	}
	bool WorldBaseGUIComponent::TickFlag() const {
		return _tick;
	}
	void WorldBaseGUIComponent::SetTickFlag(bool flag) {
		_tick = flag;
	}
}