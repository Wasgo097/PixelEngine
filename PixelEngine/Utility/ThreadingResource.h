#pragma once
#include <mutex>
namespace Utility{
	template<typename T>
	struct ThreadingResource{
		std::unique_ptr<T> _rsc;
		std::mutex _mtx;
		ThreadingResource() {
			_rsc = std::make_unique<T>();
		}
		ThreadingResource(const ThreadingResource<T>&src) = delete;
		ThreadingResource & operator=(const ThreadingResource<T>&src) = delete;
		ThreadingResource(ThreadingResource<T>&&src){
			_rsc = std::move(src._rsc);
		}
		ThreadingResource & operator=(ThreadingResource<T>&&src){
			_rsc = std::move(src._rsc);
			return *this;
		}
	};
	template<typename T>
	struct ThreadingResourceLight{
		T _rsc;
		std::mutex _mtx;
		ThreadingResourceLight() = default;
		ThreadingResourceLight(const ThreadingResourceLight<T>&src) = delete;
		ThreadingResourceLight & operator=(const ThreadingResourceLight<T>&src) = delete;
		ThreadingResourceLight(ThreadingResourceLight<T>&&src){
			_rsc = std::move(src._rsc);
		}
		ThreadingResourceLight & operator=(ThreadingResourceLight<T>&&src){
			_rsc = std::move(src._rsc);
			return *this;
		}
	};
}