#pragma once
#include "CommonHeaders.h"
namespace Core{
	class Object{
	private:
		bool _todestroy = false;
	public:
		virtual ~Object() = default;
		virtual std::string ToString(){ return ""; }
		virtual void Init(){}
		virtual void OnLoad(){}
		virtual void OnSpawn(){}
		virtual void OnDelete(){}
		void Destroy();
		bool ToDestroy();
	};
}