#pragma once
namespace Core::World {
	class BaseWorld;
}
namespace Core::World::Component {
	class WorldBaseComponent {
	public:
		WorldBaseComponent(BaseWorld* parent);
		virtual void Tick(float delta_time) = 0;
		virtual void InitComponent() {};
		virtual void EndComponent() {};
		bool TickFlag()const;
		void SetTickFlag(bool flag);
	private:
		bool _tick = false;
	protected:
		BaseWorld* _parent;
	};
}