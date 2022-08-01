#include "ForestMainCharacter.h"
#include "PXFactory/SettingsFactory.h"
#include "../WorldForForestTest.h"
#include "Tree.h"
#include "Fireball.h"
#include "PXCore/Object/Components/Collider.h"
namespace Test {
	ForestMainCharacter::ForestMainCharacter(Core::World::WorldBase* world, const Settings::ActorSettings& actor_settings, const Settings::TextureSettings& texture_settings, const Settings::AnimationSettings& animation_settings, Core::Controller::ControllerBase* controller) :
		Core::Object::ControlledActor{ world,actor_settings,texture_settings,animation_settings,controller }
	{
	}
	void ForestMainCharacter::CreateNewTree()
	{
		auto tree_settings = CREATE_SETTINGS(Settings::ActorSettings, "Cfg\\TreeActorSettings.json");
		if (auto collider = GetColliderComponent(); collider)
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
	void ForestMainCharacter::CastFireball()const {
		auto fireball_settings = CREATE_SETTINGS(Settings::ActorSettings, "Cfg\\FireballActorSettings.json");
		auto fireball_texture = CREATE_SETTINGS(Settings::TextureSettings, "Cfg\\FireballTextureSettings.json");
		auto fireball_animation = CREATE_SETTINGS(Settings::AnimationSettings, "Cfg\\FireballAnimationSettings.json");
		if (auto collider = GetColliderComponent(); collider)
			fireball_settings.position = collider->GetCollider().getPosition();
		else if (_sprite)
			fireball_settings.position = _sprite->getPosition();
		auto& velocity = fireball_settings.velocity;
		velocity.x = _velocity.x;
		velocity.y = _velocity.y;
		velocity *= 3.0f;
		if (velocity == sf::Vector2f())
			velocity.y = 300.0f;
		constexpr float PROPORTION_PARAMETER_X = 1.6f;
		constexpr float PROPORTION_PARAMETER_Y = 1.8f;
		if (velocity.x > .0f)
			fireball_settings.position.x += (GetColliderComponent()->GetCollider().getSize().x / PROPORTION_PARAMETER_X + fireball_settings.collider_size.x / PROPORTION_PARAMETER_Y);
		else if (velocity.x < .0f)
			fireball_settings.position.x -= (GetColliderComponent()->GetCollider().getSize().x / PROPORTION_PARAMETER_X + fireball_settings.collider_size.x / PROPORTION_PARAMETER_Y);
		else if (velocity.y > .0f)
			fireball_settings.position.y += (GetColliderComponent()->GetCollider().getSize().y / PROPORTION_PARAMETER_X + fireball_settings.collider_size.y / PROPORTION_PARAMETER_Y);
		else
			fireball_settings.position.y -= (GetColliderComponent()->GetCollider().getSize().y / PROPORTION_PARAMETER_X + fireball_settings.collider_size.y / PROPORTION_PARAMETER_Y);
		_world->SpawnAnimatedActor<Fireball>(fireball_settings, fireball_texture, fireball_animation);
	}
}