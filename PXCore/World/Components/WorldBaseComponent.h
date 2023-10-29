#pragma once
namespace Core::World {
	class WorldBase;
}
namespace Core::World::Component {
	class WorldBaseComponent {
	public:
		WorldBaseComponent(WorldBase* parent);
		virtual void Tick(float delta_time) = 0;
		virtual void InitComponent() = 0;
		virtual void EndComponent() = 0;
		bool TickFlag()const;
		void SetTickFlag(bool flag);
	private:
		bool _tick = false;
	protected:
		WorldBase* _parent;
		bool _initialized = true;
	};
}