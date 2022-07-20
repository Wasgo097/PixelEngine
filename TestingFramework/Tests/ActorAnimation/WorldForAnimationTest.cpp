#include "WorldForAnimationTest.h"
#include <iostream>
#include "ControllerForAnimationTest.h"
using namespace Core;
namespace Test {
	WorldForAnimationTest::WorldForAnimationTest(const Settings::WorldSettings& worlsettings, Core::Engine* parent):WorldBase(worlsettings,parent){
		_main_controller = std::make_unique<Test::ControllerForAnimationTest>(this);
	}
	void WorldForAnimationTest::CheckQuit(){
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			_quit = true;
			std::cout << "Escape pressed, WorldForAnimationTest is quit\n";
		}
	}
	void WorldForAnimationTest::InitWorld(){
		WorldBase::InitWorld();
		std::cout << "Init WorldForAnimationTest world\n";
	}
	void WorldForAnimationTest::EndWorld(){
		WorldBase::EndWorld();
		std::cout << "End WorldForAnimationTest world\n";
	}
	void WorldForAnimationTest::Draw(sf::RenderWindow& window)	{
		window.clear(sf::Color::Green);
		WorldBase::Draw(window);
	}
}