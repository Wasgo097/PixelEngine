#include "BlockEvent.h"

namespace Test {
	BlockEvent::BlockEvent(const ArgumentParser& parser) :BaseTest(parser)
	{
	}
	bool BlockEvent::PrepareTest()
	{
		sf::RenderWindow window(sf::VideoMode(800, 600), "TGUI window");
		tgui::Gui gui(window);
		if (!RunExample(gui)) {
			return false;
		}
		while (window.isOpen()) {
			sf::Event event;
			while (window.pollEvent(event)) {
				gui.handleEvent(event);

				if (event.type == sf::Event::Closed)
					window.close();
			}

			window.clear();
			gui.draw();
			window.display();
		}
		return true;
	}
	bool BlockEvent::RunTest()
	{
		try {
			if (PrepareTest())
				return true;
			return false;
		}
		catch (std::exception& ex) {

			std::cerr << "BlockEvent exception " << ex.what() << "\n";
		}
		return false;
	}
	bool BlockEvent::RunExample(tgui::GuiBase& gui)
	{
		_guiPtr = &gui;

		// Create a button to open the window.
		// Once the window is open you won't be able to press it again until the window closes.
		auto button = tgui::Button::create("Open window");
		button->onPress([this] { OpenWindow(); });
		gui.add(button);
		return true;
	}
	void BlockEvent::OpenWindow()
	{
		// Create the transparent panel that covers the existing contents
		auto panel = tgui::Panel::create({ "100%", "100%" });
		panel->getRenderer()->setBackgroundColor({ 0, 0, 0, 175 });
		_guiPtr->add(panel, "TransparentBackground");

		// Create the child window and make sure to add it to the panel instead of the gui
		auto window = tgui::ChildWindow::create();
		panel->add(window);

		// Remove the panel when the window is closed
		window->onClose([this] { CloseWindow(); });
	}
	void BlockEvent::CloseWindow()
	{
		// Find the transparent panel and destroy it
		_guiPtr->remove(_guiPtr->get("TransparentBackground"));
	}
}