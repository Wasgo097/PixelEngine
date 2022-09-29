#include "ControllerForForestTest.h"
#include "Actors/ForestMainCharacter.h"
#include "PXFactory/SettingsFactory.h"
#include "PXParticle/BaseImplementations/Smoke.h"
namespace Test {
	ControllerForForestTest::ControllerForForestTest(Core::World::WorldBase* world, const Settings::WorldSettings& world_settings) :ControllerBase(world, world_settings) {
	}

	void ControllerForForestTest::InitMainCharacterInputBindings() {
		Core::Controller::Key key;
		key.input_type = Core::Controller::InputType::MouseInput;
		key.event_type = sf::Event::MouseButtonPressed;
		key.mouse_button = sf::Mouse::Left;
		key.repeatable = false;
		_actions[key] = [this](std::shared_ptr<Core::Object::ControlledActor> actor) {
			//if (auto ptr = std::dynamic_pointer_cast<ForestMainCharacter>(actor); ptr) {
			//	//ptr->CastFireball();
			//	//ptr->CreateNewTree();
			//}
			_world_parent->PushNewParticles(std::make_unique<::Particle::Smoke>(*actor->GetPosition(), Factory::ParticleSystemSettings::Size::big));
		};
		key.repeatable = true;
		//key.mouse_button = sf::Mouse::Right;
		//_actions[key] = [](std::shared_ptr<Core::Object::ControlledActor> actor) {
		//	if (auto ptr = std::dynamic_pointer_cast<ForestMainCharacter>(actor); ptr) {
		//		ptr->EraseTree();
		//	}
		//};
		key.input_type = Core::Controller::InputType::KeyboardInput;
		key.event_type = sf::Event::KeyPressed;
		key.keyboard_button = sf::Keyboard::W;
		_actions[key] = [this](std::shared_ptr<Core::Object::ControlledActor> actor) {
			if (CheckMoveIsPossible(sf::Vector2f(0, -100.0))) {
				actor->Move(sf::Vector2f(0, -100.0));
				if (auto position = actor->GetPosition(); position)
					_world_parent->RefreshView(*position);
			}
		};
		key.keyboard_button = sf::Keyboard::S;
		_actions[key] = [this](std::shared_ptr<Core::Object::ControlledActor> actor) {
			if (CheckMoveIsPossible(sf::Vector2f(0, 100.0))) {
				actor->Move(sf::Vector2f(0, 100.0));
				if (auto position = actor->GetPosition(); position)
					_world_parent->RefreshView(*position);
			}
		};
		key.keyboard_button = sf::Keyboard::A;
		_actions[key] = [this](std::shared_ptr<Core::Object::ControlledActor> actor) {
			if (CheckMoveIsPossible(sf::Vector2f(-100.0, 0))) {
				actor->Move(sf::Vector2f(-100.0, 0));
				if (auto position = actor->GetPosition(); position)
					_world_parent->RefreshView(*position);
			}
		};
		key.keyboard_button = sf::Keyboard::D;
		_actions[key] = [this](std::shared_ptr<Core::Object::ControlledActor> actor) {
			if (CheckMoveIsPossible(sf::Vector2f(100.0, 0))) {
				actor->Move(sf::Vector2f(100.0, 0));
				if (auto position = actor->GetPosition(); position)
					_world_parent->RefreshView(*position);
			}
		};
	}
	void ControllerForForestTest::InitMainCharacter() {
		auto actor_settings = CREATE_SETTINGS(Settings::ActorSettings, "Cfg\\MainActorSettings.json");
		auto texture_settings = CREATE_SETTINGS(Settings::TextureSettings, "Cfg\\MainTextureSettings.json");
		auto animation_settings = CREATE_SETTINGS(Settings::AnimationSettings, "Cfg\\MainAnimationSettings.json");
		_main_character = std::make_shared<ForestMainCharacter>(_world_parent, actor_settings, texture_settings, animation_settings, this);
	}
}