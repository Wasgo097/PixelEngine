#include "WorldForAnimationTest.h"
#include "Utility/CommonHeaders.h"
#include "ControllerForAnimationTest.h"
using namespace Core;
namespace Test {
	WorldForAnimationTest::WorldForAnimationTest(const Settings::WorldSettings& worlsettings, Core::Engine* parent):WorldBase(worlsettings,parent){
		_maincontroller = std::make_unique<Test::ControllerForAnimationTest>(this);
		_maincontroller->InitMainCharacterInputBindings();
		_maincontroller->InitMainCharacter();
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
	void WorldForAnimationTest::Update(float delta)
	{
		//std::cout << "WorldForAnimationTest update time " << delta << "\n";
		Core::WorldBase::Update(delta);
	}
}