#pragma once
namespace Core::Object::Components {
	class ActorComponentBase {
	public:
		virtual ~ActorComponentBase() = default;
		virtual void Tick(float delta_time) = 0;
		virtual void InitComponent() {};
		virtual void EndComponent() {};
		bool TickFlag()const;
		void SetTickFlag(bool flag);
	private:
		bool _tick = false;
	};
}