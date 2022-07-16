#include "ForestMainCharacter.h"
#include "PXFactory/SettingsFactory.h"
#include "PXCore/World/WorldBase.h"
#include "Tree.h"
namespace Test {
	ForestMainCharacter::ForestMainCharacter(Core::World::WorldBase* world, const Settings::ActorSettings& actor_settings, const Settings::TextureSettings& texture_settings, const Settings::AnimationSettings& animation_settings, Core::Controller::ControllerBase* controller):
		Core::Object::ControlledActor{world,actor_settings,texture_settings,animation_settings,controller}
	{
	}
	void ForestMainCharacter::CreateNewTree()
	{
		auto tree_settings = CREATE_SETTINGS(Settings::ActorSettings, "Cfg\\TreeActorSettings.json");
		if (_collider)
			tree_settings.position = _collider->getPosition();
		else if(_sprite)
			tree_settings.position = _sprite->getPosition();
		auto tree_texture = CREATE_SETTINGS(Settings::TextureSettings, "Cfg\\TreeTextureSettings.json");
		_created_tree.push_back(_world->SpawnActor<Tree>(tree_settings, tree_texture));
	}
	void ForestMainCharacter::EraseTree()
	{
		if (!_created_tree.empty()) {
			auto& tree = _created_tree.front();
			tree->Destroy();
			_created_tree.erase(_created_tree.begin());
		}
	}
}