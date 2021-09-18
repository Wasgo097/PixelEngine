#include "Core/ActorManager.h"
namespace Core{
	ActorManager::ActorManager(size_t buffer_size, int gcfrequentlevel):_frequencylevel(gcfrequentlevel){
		_firststage._rsc.reserve(buffer_size);
		_secondstage._rsc.reserve(buffer_size);
		_constactor._rsc.reserve(buffer_size);
	}
}