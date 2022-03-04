#pragma once
#include "Core/WorldBase.h"
namespace Core {
	class EmptyWorld:public WorldBase{
	public:
		EmptyWorld(const Settings::WorldSettings& worlsettings = Settings::WorldSettings(), Engine* parrent = nullptr):WorldBase(worlsettings,parrent){}
	protected:
		// Inherited via WorldBase
		virtual void CheckQuit() override;
		virtual void InitWorld() override;
		virtual void EndWorld() override;
	};
}
