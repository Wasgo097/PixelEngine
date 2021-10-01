#pragma once
#include "AnimatedActor.h"
namespace Core{
	class ControlledActor:public AnimatedActor{
		ControlledActor(const ControlledActor&) = delete;
		ControlledActor(ControlledActor&&) = delete;
		ControlledActor& operator=(const ControlledActor&) = delete;
		ControlledActor& operator=(ControlledActor&&) = delete;
		virtual ~ControlledActor() = default;
	protected:

	};
}