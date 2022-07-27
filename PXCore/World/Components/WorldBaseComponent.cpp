#include "WorldBaseComponent.h"
namespace Core::World::Component {
	WorldBaseComponent::WorldBaseComponent(BaseWorld* parent) :_parent{ parent } {
	}
	bool WorldBaseComponent::TickFlag() const {
		return _tick;
	}
	void WorldBaseComponent::SetTickFlag(bool flag) {
		_tick = flag;
	}
}