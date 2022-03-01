#include "Controller/ControllerBase.h"
#include "Core/Engine.h"
#include "Objects/ControlledActor.h"
namespace Controller {
	ControllerBase::ControllerBase(){
		SetMainCharacterInputBindings();
	}
}