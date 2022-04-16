#pragma once
#include <mutex>
namespace Utility{
	template<typename T>
	struct ThreadingResource{
		std::unique_ptr<T> Rsc;
		std::mutex Mtx;
		ThreadingResource() {
			Rsc = std::make_unique<T>();
		}
		ThreadingResource(const ThreadingResource<T>&src) = delete;
		ThreadingResource & operator=(const ThreadingResource<T>&src) = delete;
		ThreadingResource(ThreadingResource<T>&&src){
			Rsc = std::move(src.Rsc);
		}
		ThreadingResource & operator=(ThreadingResource<T>&&src){
			Rsc = std::move(src.Rsc);
			return *this;
		}
	};
	template<typename T>
	struct ThreadingResourceLight{
		T Rsc;
		std::mutex Mtx;
		ThreadingResourceLight() = default;
		ThreadingResourceLight(const ThreadingResourceLight<T>&src) = delete;
		ThreadingResourceLight & operator=(const ThreadingResourceLight<T>&src) = delete;
		ThreadingResourceLight(ThreadingResourceLight<T>&&src){
			Rsc = std::move(src.Rsc);
		}
		ThreadingResourceLight & operator=(ThreadingResourceLight<T>&&src){
			Rsc = std::move(src.Rsc);
			return *this;
		}
	};
}