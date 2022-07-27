#include "WorldForAnimationTest.h"
#include "ControllerForAnimationTest.h"
using namespace Core;
namespace Test {
	WorldForAnimationTest::WorldForAnimationTest(const Settings::WorldSettings& worlsettings, Core::Engine* parent):WorldBase(worlsettings,parent){
		_main_controller = std::make_unique<Test::ControllerForAnimationTest>(this);
	}
	void WorldForAnimationTest::CheckQuit(){
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			_quit = true;
		}
	}
}