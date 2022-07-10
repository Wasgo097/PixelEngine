#include "WorldForForestTest.h"
#include <iostream>
#include "ControllerForForestTest.h"
#include "Actors/Tree.h"
using namespace Core;
namespace Test {
	WorldForForestTest::WorldForForestTest(const Settings::WorldSettings& worlsettings, Core::Engine* parent):WorldBase(worlsettings,parent){
		_main_controller = std::make_unique<Test::ControllerForForestTest>(this);
	}
	void WorldForForestTest::CheckQuit(){
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			_quit = true;
			std::cout << "Escape pressed, WorldForForestTest is quit\n";
		}
	}
	void WorldForForestTest::InitWorld(){
		WorldBase::InitWorld();
		SpawnConstActor<Tree>(
			Settings::ActorSettings(ActorsEnums::CollisionType::Collision, ActorsEnums::ActorType::Static, sf::Vector2f(500, 500), sf::Vector2f(96, 96), sf::Vector2f(), true),
			Settings::TextureSettings("Resource\\Actors\\Tree.jpg", true, false));
		std::cout << "Init WorldForForestTest world\n";
	}
	void WorldForForestTest::EndWorld(){
		WorldBase::EndWorld();
		std::cout << "End WorldForForestTest world\n";
	}
	void WorldForForestTest::Draw(sf::RenderWindow& window)	{
		window.clear(sf::Color::Green);
		WorldBase::Draw(window);
	}
}