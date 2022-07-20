#pragma once
#include "ActorComponentBase.h"
namespace Core::Object::Components {
	class Collider:public ActorComponentBase{
	public:
		Collider(Core::Object::Actor* parent);
		// Inherited via ActorComponentBase
		virtual void Tick(float delta_time) override;
	};
}