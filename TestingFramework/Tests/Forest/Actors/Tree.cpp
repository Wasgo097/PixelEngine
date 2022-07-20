#include "Tree.h"
#include <iostream>
namespace Test {
	Tree::Tree(Core::World::WorldBase* world, const Settings::ActorSettings& actor_settings, const Settings::TextureSettings& texture_settings) :
		Core::Object::Actor{ world,actor_settings,texture_settings }
	{
	}
	void Tree::SecondPassed() {
		std::cout << "Second passed on tree\n";
		_growing_counter++;
		if (_growing_counter < 10) {
			auto currect_scale = _sprite->getScale();
			currect_scale.x += 0.1f;
			currect_scale.y += 0.1f;
			_sprite->setScale(currect_scale);
		}
	}
}