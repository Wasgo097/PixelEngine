#include "ActorComponentBase.h"
namespace Core::Object::Components {
	bool ActorComponentBase::TickFlag() const{
		return _tick;
	}
	void ActorComponentBase::SetTickFlag(bool flag){
		_tick = flag;
	}
}