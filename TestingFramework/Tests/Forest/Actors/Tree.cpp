#include "Tree.h"
namespace Test {
	Tree::Tree(Core::World::WorldBase* world, const Settings::ActorSettings& actor_settings, const Settings::TextureSettings& texture_settings) :
		Core::Object::Actor{ world,actor_settings,texture_settings }	{
	}
	void Tree::Init() {
		Actor::Init();
		auto currect_scale = _sprite->getScale();
		currect_scale.x += 1.0f;
		currect_scale.y += 1.0f;
		_sprite->setScale(currect_scale);
		if (auto collider = GetColliderComponent(); collider)
			collider->GetCollider().setScale(currect_scale);
	}
	void Tree::SecondPassed(unsigned int second) {
		_growing_counter++;
		if (_growing_counter < 10) {
			auto currect_scale = _sprite->getScale();
			currect_scale.x += 0.1f;
			currect_scale.y += 0.1f;
			_sprite->setScale(currect_scale);
			if (auto collider = GetTComponent<Core::Object::Components::Collider>(); collider)
				collider->GetCollider().setScale(currect_scale);
		}
	}
}