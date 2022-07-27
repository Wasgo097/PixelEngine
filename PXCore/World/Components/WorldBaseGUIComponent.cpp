#include "WorldBaseGUIComponent.h"
namespace Core::World::Component {
	WorldBaseGUIComponent::WorldBaseGUIComponent(BaseWorldGUI* parent, tgui::Gui* gui) :_parent{ parent }, _gui{ gui }	{
	}
}