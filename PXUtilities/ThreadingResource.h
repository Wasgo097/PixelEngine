#pragma once
#include <mutex>
#include <memory>
#include <concepts>
namespace Utility {
	template<typename T>
		requires std::is_default_constructible_v<T>
	struct SharedThreadingResource {
		std::shared_ptr<T> rsc;
		std::shared_ptr<std::mutex> mtx;
		SharedThreadingResource() {
			rsc = std::make_shared<T>();
			mtx = std::make_shared<std::mutex>();
		}
		SharedThreadingResource(const SharedThreadingResource<T>& src) {
			rsc = src.rsc;
			mtx = src.mtx;
		}
		SharedThreadingResource& operator=(const SharedThreadingResource<T>& src) {
			rsc = src.rsc;
			mtx = src.mtx;
			return *this;
		}
		SharedThreadingResource(SharedThreadingResource<T>&& src) {
			rsc = std::move(src.rsc);
			mtx = std::move(src.mtx);
		}
		SharedThreadingResource& operator=(SharedThreadingResource<T>&& src) {
			rsc = std::move(src.rsc);
			mtx = std::move(src.mtx);
			return *this;
		}
	};
	template<typename T>
		requires std::is_default_constructible_v<T>
	struct ThreadingResourceLight {
		std::unique_ptr<T> rsc;
		std::mutex mtx;
		ThreadingResourceLight() {
			rsc = std::make_unique<T>();
		}
		ThreadingResourceLight(const ThreadingResourceLight<T>& src) = delete;
		ThreadingResourceLight& operator=(const ThreadingResourceLight<T>& src) = delete;
		ThreadingResourceLight(ThreadingResourceLight<T>&& src) {
			rsc = std::move(src.rsc);
			mtx = std::move(src.mtx);
		}
		ThreadingResourceLight& operator=(ThreadingResourceLight<T>&& src) {
			rsc = std::move(src.rsc);
			mtx = std::move(src.mtx);
			return *this;
		}
	};
}