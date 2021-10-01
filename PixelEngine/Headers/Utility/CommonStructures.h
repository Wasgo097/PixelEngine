#pragma once
#include <mutex>
namespace Utility{
	template<typename T>
	struct ThreadingResource{
	public:
		std::unique_ptr<T> _rsc;
		std::mutex _mtx;
	public:
		ThreadingResource() = default;
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
	public:
		T _rsc;
		std::mutex _mtx;
	public:
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