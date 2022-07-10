#include "Tree.h"
namespace Test {
	Tree::Tree(Core::World::WorldBase* world, const Settings::ActorSettings& actor_settings, const Settings::TextureSettings& texture_settings):
		Core::Object::Actor{world,actor_settings,texture_settings}
	{
	}
}