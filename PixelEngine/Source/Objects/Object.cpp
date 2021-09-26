#include "Objects/Object.h"
namespace Core{
	Object::~Object() = default;
	void Object::Destroy(){
		_todestroy = true;
	}
	bool Object::ToDestroy(){
		return _todestroy;
	}
}
