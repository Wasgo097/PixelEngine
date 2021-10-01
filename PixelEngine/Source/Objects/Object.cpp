#include "CommonHeaders.h"
#include "Objects/Object.h"
namespace Core{
	Object::~Object(){
		OnDelete();
	}
	void Object::Destroy(){
		_todestroy = true;
	}
	bool Object::ToDestroy(){
		return _todestroy;
	}
}
