#pragma once
#include "PXCore/World/WorldBaseGUI.h"
#include "PXCore/Time/TimeManager.h"
#include "PXCore/World/Components/ActorsCounter.h"
namespace Test {
	class Tree;
	class WorldForForestTest :public Core::World::WorldBaseGUI {
	public:
		WorldForForestTest(const Settings::WorldSettings& world_settings = Settings::WorldSettings(), Core::Engine* parrent = nullptr);
	public:
		virtual void CheckQuit()override;
		virtual void Draw(sf::RenderWindow& window)override;
		virtual void InitWorld()override;
		void AddTree(std::shared_ptr<Tree> tree);
		void RemoveTree(std::shared_ptr<Tree> tree);
	protected:
		// Inherited via WorldBase
		virtual void CreateWorldBaseComponents() override {}
		// Inherited via WorldBaseGUI
		virtual void CreateWorldBaseGUIComponents() override;
		virtual void InitGuiSettup();
		void DEBUGDrawDeadZone(sf::RenderWindow& window)const;
		std::shared_ptr<Core::World::Component::ActorsCounter> GetActorsCounter()const;
		Core::Time::TimeManager _tree_timer;
		std::list<std::shared_ptr<Tree>> _created_trees;
	};
}
