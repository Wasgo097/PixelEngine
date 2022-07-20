#pragma once
#include "PXCore/Object/ControlledActor.h"
#include <vector>
namespace Test {
	class Tree;
	class ForestMainCharacter :public Core::Object::ControlledActor
	{
	public:
		ForestMainCharacter(Core::World::WorldBase* world, const Settings::ActorSettings& actor_settings, const Settings::TextureSettings& texture_settings, const Settings::AnimationSettings& animation_settings, Core::Controller::ControllerBase* controller);
		void CreateNewTree();
		void EraseTree();
	protected:
		std::vector<std::shared_ptr<Tree>> _created_tree;
	};
}