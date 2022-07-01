#pragma once
#include <string>
namespace Core{
	class Object{
	public:
		virtual ~Object() = default;
		virtual std::string ToString()const { return "Default Object ToString"; }
		virtual void Init(){}
		virtual void OnLoad(){}
		virtual void OnSpawn(){}
		virtual void OnDelete(){}
		void Destroy();
		bool ToDestroy();
	private:
		bool _to_destroy = false;
	};
}