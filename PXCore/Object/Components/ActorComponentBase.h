#pragma once
namespace Core::Object {
	class Actor;
}
namespace Core::Object::Components {
	class ActorComponentBase {
	public:
		ActorComponentBase(Core::Object::Actor* parent=nullptr);
		virtual ~ActorComponentBase() = default;
		virtual void Tick(float delta_time) = 0;
		virtual void InitComponent() {};
		virtual void EndComponent() {};
		bool TickFlag()const;
		void SetTickFlag(bool flag);
	private:
		bool _tick = false;
	protected:
		Core::Object::Actor* _parent;
		bool _initialized = false;
	};
}