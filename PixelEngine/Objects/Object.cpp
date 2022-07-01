#include "Utility/CommonHeaders.h"
#include "Object.h"
namespace Core{
	void Object::Destroy(){
		_to_destroy = true;
	}
	bool Object::ToDestroy(){
		return _to_destroy;
	}
}
