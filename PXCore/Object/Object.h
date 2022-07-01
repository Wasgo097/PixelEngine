#pragma once
#include <string>
namespace Core::Object{
	class Object{
	public:
		virtual ~Object() = default;
		virtual std::string ToString()const { return "Default Object ToString"; }
		virtual void Init(){}
		virtual void OnLoad(){}
		virtual void OnSpawn(){}
		virtual void OnDelete(){}
		void Destroy() { _to_destroy = true; }
		bool ToDestroy()const { return _to_destroy; }
	private:
		bool _to_destroy = false;
	};
}