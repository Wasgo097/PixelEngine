#include "MainMenuWorld.h"
#include "PXCore/Engine.h"
namespace Test {
	MainMenuWorld::MainMenuWorld(const Settings::WorldSettings& world_settings, Core::Engine* parent) :WorldBase(world_settings, parent), _gui(*parent->GetWindow()) {
	}
	void MainMenuWorld::Draw(sf::RenderWindow& window) {
		WorldBase::Draw(window);
		window.clear(sf::Color::Green);
		_gui.draw();
	}
	void MainMenuWorld::CheckQuit() {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			_quit = true;
	}
	void MainMenuWorld::InitWorld() {
		auto picture = tgui::Picture::create("Resource\\GUI\\fantasy_background.png");
		picture->setSize({ "100%", "100%" });
		_gui.add(picture);

		_initialized = true;
	}
}