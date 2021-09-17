#pragma once
#include "CommonHeaders.h"
#include <Objects/Actor.h>
namespace Core{
	class ActorManager{
	private:
		std::vector<std::shared_ptr<Actor>> _allactors;
	};
}
