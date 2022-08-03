#include "WorldForAnimationTest.h"
#include "ControllerForAnimationTest.h"
using namespace Core;
namespace Test {
	WorldForAnimationTest::WorldForAnimationTest(const Settings::WorldSettings& world_settings, Core::Engine* parent):WorldBase(world_settings,parent){
		_main_controller = std::make_unique<Test::ControllerForAnimationTest>(this, world_settings);
	}
	void WorldForAnimationTest::CheckQuit(){
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			_quit = true;
		}
	}
	void WorldForAnimationTest::DrawMap(sf::RenderWindow& window)
	{
	}
}