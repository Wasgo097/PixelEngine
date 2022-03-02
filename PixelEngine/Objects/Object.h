#pragma once
namespace Core{
	class Object{
	private:
		bool _todestroy = false;
	public:
		virtual ~Object();
		virtual std::string ToString()const { return "Default Object ToString"; }
		virtual void Init(){}
		virtual void OnLoad(){}
		virtual void OnSpawn(){}
		virtual void OnDelete(){}
		void Destroy();
		bool ToDestroy();
	};
}