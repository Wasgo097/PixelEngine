#include "ForestMainCharacter.h"
#include "PXFactory/SettingsFactory.h"
#include "../WorldForForestTest.h"
#include "Tree.h"
#include "PXCore/Object/Components/Collider.h"
namespace Test {
	ForestMainCharacter::ForestMainCharacter(Core::World::WorldBase* world, const Settings::ActorSettings& actor_settings, const Settings::TextureSettings& texture_settings, const Settings::AnimationSettings& animation_settings, Core::Controller::ControllerBase* controller) :
		Core::Object::ControlledActor{ world,actor_settings,texture_settings,animation_settings,controller }
	{
	}
	void ForestMainCharacter::CreateNewTree()
	{
		auto tree_settings = CREATE_SETTINGS(Settings::ActorSettings, "Cfg\\TreeActorSettings.json");
		if (auto collider = GetTComponent<Core::Object::Components::Collider>(); collider)
			tree_settings.position = collider->GetCollider().getPosition();
		else if (_sprite)
			tree_settings.position = _sprite->getPosition();
		auto tree_texture = CREATE_SETTINGS(Settings::TextureSettings, "Cfg\\TreeTextureSettings.json");
		auto tree = _world->SpawnActor<Tree>(tree_settings, tree_texture);
		_created_tree.push_back(tree);
		if (auto forest_world = dynamic_cast<WorldForForestTest*>(_world); forest_world != nullptr)
			forest_world->AddTree(tree);
	}
	void ForestMainCharacter::EraseTree()
	{
		if (!_created_tree.empty()) {
			auto tree = _created_tree.front();
			tree->Destroy();
			_created_tree.erase(_created_tree.begin());
			if (auto forest_world = dynamic_cast<WorldForForestTest*>(_world); forest_world != nullptr)
				forest_world->RemoveTree(tree);
		}
	}
}