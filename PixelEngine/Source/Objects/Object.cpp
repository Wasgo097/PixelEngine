#include "Objects/Object.h"
namespace Core{
	void Object::Destroy(){
		_todestroy = true;
	}
	bool Object::ToDestroy(){
		return _todestroy;
	}
}
