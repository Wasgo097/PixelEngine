#pragma once
#include "Core/World/WorldBase.h"
namespace Core {
	class EmptyWorld:public WorldBase{
	public:
		EmptyWorld(const Settings::WorldSettings& worlsettings = Settings::WorldSettings(), Engine* parrent = nullptr);
	public:
		// Inherited via WorldBase
		virtual void InitWorld() override;
		virtual void EndWorld() override;
		virtual void CheckQuit() override;
	};
}