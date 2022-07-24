#pragma once
#include <string>
#include <memory>
namespace Core::Object{
	class Object{
	public:
		virtual ~Object() = default;
		virtual std::string ToString()const { return "Default Object ToString"; }
		virtual void Init(){}
		virtual void OnSpawn(){}
		virtual void OnDelete(){}
		virtual void OnOverlap(std::shared_ptr<Object> other) {}
		virtual void OnCollide(std::shared_ptr<Object> other) {}
		void Destroy() { _to_destroy = true; }
		bool ToDestroy()const { return _to_destroy; }
	private:
		bool _to_destroy = false;
	};
}