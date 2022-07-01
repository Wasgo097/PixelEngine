#pragma once
#include <mutex>
//todo Refactor ThreadingResources
//ThReadingResources should contgains shared pointes to rsc and mtx
namespace Utility{
	template<typename T>
	struct ThreadingResource{
		std::unique_ptr<T> rsc;
		std::mutex mtx;
		ThreadingResource() {
			rsc = std::make_unique<T>();
		}
		ThreadingResource(const ThreadingResource<T>&src) = delete;
		ThreadingResource & operator=(const ThreadingResource<T>&src) = delete;
		ThreadingResource(ThreadingResource<T>&&src){
			rsc = std::move(src.rsc);
		}
		ThreadingResource & operator=(ThreadingResource<T>&&src){
			rsc = std::move(src.rsc);
			return *this;
		}
	};
	template<typename T>
	struct ThreadingResourceLight{
		T rsc;
		std::mutex mtx;
		ThreadingResourceLight() = default;
		ThreadingResourceLight(const ThreadingResourceLight<T>&src) = delete;
		ThreadingResourceLight & operator=(const ThreadingResourceLight<T>&src) = delete;
		ThreadingResourceLight(ThreadingResourceLight<T>&&src){
			rsc = std::move(src.rsc);
		}
		ThreadingResourceLight & operator=(ThreadingResourceLight<T>&&src){
			rsc = std::move(src.rsc);
			return *this;
		}
	};
}