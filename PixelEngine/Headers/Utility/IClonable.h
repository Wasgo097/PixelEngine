#pragma once
#include <memory>
namespace Core{
	class Object;
}
namespace Utility{
	class IClonable{
		virtual Core::Object* Clone() = 0;
		virtual std::shared_ptr<Core::Object> CloneToShared() = 0;
	};
	template<typename T>
	class IClonableT{
		virtual T* Clone() = 0;
		virtual std::shared_ptr<T> CloneToShared() = 0;
	};
}