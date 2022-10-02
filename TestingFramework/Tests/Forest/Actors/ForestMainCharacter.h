#pragma once
#include "PXCore/Object/ControlledActor.h"
#include <vector>
#include <memory>
#include "PXSound/SoundEffect.h"
namespace Test {
	class Tree;
	class ForestMainCharacter :public Core::Object::ControlledActor {
	public:
		ForestMainCharacter(Core::World::WorldBase* world, const Settings::ActorSettings& actor_settings, const Settings::TextureSettings& texture_settings, const Settings::AnimationSettings& animation_settings, Core::Controller::ControllerBase* controller);
		virtual void Move(const sf::Vector2f& velocity)override;
		void CreateNewTree();
		void EraseTree();
		void CastFireball()const;
	protected:
		std::vector<std::shared_ptr<Tree>> _created_tree;
		std::weak_ptr<Sound::SoundEffect> _step_sound_effect;
		sf::SoundBuffer _step_sound_effect_buffer;
	};
}