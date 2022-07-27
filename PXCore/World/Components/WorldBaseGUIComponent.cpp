#include "WorldBaseGUIComponent.h"
namespace Core::World::Component {
	WorldBaseGUIComponent::WorldBaseGUIComponent(WorldBaseGUI* parent, tgui::Gui* gui) :_parent{ parent }, _gui{ gui }	{
	}
	bool WorldBaseGUIComponent::TickFlag() const {
		return _tick;
	}
	void WorldBaseGUIComponent::SetTickFlag(bool flag) {
		_tick = flag;
	}
}