#include "ActorComponentBase.h"
namespace Core::Object::Components {
	ActorComponentBase::ActorComponentBase(Core::Object::Actor* parent):_parent(parent){
	}
	bool ActorComponentBase::TickFlag() const{
		return _tick;
	}
	void ActorComponentBase::SetTickFlag(bool flag){
		_tick = flag;
	}
}