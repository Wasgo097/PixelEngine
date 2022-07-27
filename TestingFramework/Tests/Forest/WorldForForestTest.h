#pragma once
#include "PXCore/World/WorldBase.h"
#include "PXCore/Time/TimeManager.h"
namespace Test {
	class Tree;
	class WorldForForestTest :public Core::World::WorldBase{
	public:
		WorldForForestTest(const Settings::WorldSettings& worlsettings = Settings::WorldSettings(), Core::Engine* parrent = nullptr);
	public:
		virtual void CheckQuit()override;
		virtual void InitWorld()override;
		void AddTree(std::shared_ptr<Tree> tree);
		void RemoveTree(std::shared_ptr<Tree> tree);
	protected:
		std::shared_ptr<Core::Time::TimeManager> _tree_timer;
		std::list<std::shared_ptr<Tree>> _created_trees;
	};
}
