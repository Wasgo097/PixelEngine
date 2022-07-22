#pragma once
#include <mutex>
#include <memory>
#include <concepts>
namespace Utility {
	template<typename T>
		requires std::is_default_constructible_v<T>
	struct ThreadingResourceShared {
		std::shared_ptr<T> rsc;
		std::shared_ptr<mutable std::recursive_mutex> mtx;
		ThreadingResourceShared() {
			rsc = std::make_shared<T>();
			mtx = std::make_shared<std::recursive_mutex>();
		}
		ThreadingResourceShared(const ThreadingResourceShared<T>& src) {
			rsc = src.rsc;
			mtx = src.mtx;
		}
		ThreadingResourceShared& operator=(const ThreadingResourceShared<T>& src) {
			rsc = src.rsc;
			mtx = src.mtx;
			return *this;
		}
		ThreadingResourceShared(ThreadingResourceShared<T>&& src) {
			rsc = std::move(src.rsc);
			mtx = std::move(src.mtx);
		}
		ThreadingResourceShared& operator=(ThreadingResourceShared<T>&& src) {
			rsc = std::move(src.rsc);
			mtx = std::move(src.mtx);
			return *this;
		}
	};
	template<typename T>
		requires std::is_default_constructible_v<T>
	struct ThreadingResourceLight {
		std::unique_ptr<T> rsc;
		mutable std::recursive_mutex mtx;
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