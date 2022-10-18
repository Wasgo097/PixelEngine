#include "LoginExample.h"
#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>

namespace Test {
	LoginExample::LoginExample(const ArgumentParser& parser) :BaseTest(parser) {
	}
	bool LoginExample::PrepareTest() {
		sf::RenderWindow window(sf::VideoMode(800, 600), "TGUI window");

		tgui::Gui gui(window);
		if (!runExample(gui))
			return false;

		gui.mainLoop();
		return true;
	}
	bool LoginExample::RunTest() {
		try {
			if (PrepareTest())
				return true;
			return false;
		}
		catch (std::exception& ex) {
			std::cerr << "LoginExample exception " << ex.what() << "\n";
		}
		return false;
	}
	void LoginExample::login(tgui::EditBox::Ptr username, tgui::EditBox::Ptr password) {
		std::cout << "Username: " << username->getText() << std::endl;
		std::cout << "Password: " << password->getText() << std::endl;
	}
	void LoginExample::updateTextSize(tgui::GuiBase& gui) {
		// Update the text size of all widgets in the gui, based on the current window height
		const float windowHeight = gui.getView().getRect().height;
		gui.setTextSize(static_cast<unsigned int>(0.07f * windowHeight)); // 7% of height
	}
	bool LoginExample::loadWidgets(tgui::GuiBase& gui) {
		// Specify an initial text size instead of using the default value
		updateTextSize(gui);

		// We want the text size to be updated when the window is resized
		gui.onViewChange([&gui, this] { updateTextSize(gui); });

		// Create the background image
		// The picture is of type tgui::Picture::Ptr which is actually just a typedef for std::shared_widget<tgui::Picture>
		// The picture will fit the entire window and will scale with it
		auto picture = tgui::Picture::create("Resource\\GUI\\xubuntu_bg_aluminium.jpg");
		picture->setSize({ "100%", "100%" });
		gui.add(picture);

		// Create the username edit box
		// Similar to the picture, we set a relative position and size
		// In case it isn't obvious, the default text is the text that is displayed when the edit box is empty
		auto editBoxUsername = tgui::EditBox::create();
		editBoxUsername->setSize({ "66.67%", "12.5%" });
		editBoxUsername->setPosition({ "16.67%", "16.67%" });
		editBoxUsername->setDefaultText("Username");
		gui.add(editBoxUsername);

		// Create the password edit box
		// We copy the previous edit box here and keep the same size
		auto editBoxPassword = tgui::EditBox::copy(editBoxUsername);
		editBoxPassword->setPosition({ "16.67%", "41.6%" });
		editBoxPassword->setPasswordCharacter('*');
		editBoxPassword->setDefaultText("Password");
		gui.add(editBoxPassword);

		// Create the login button
		auto button = tgui::Button::create("Login");
		button->setSize({ "50%", "16.67%" });
		button->setPosition({ "25%", "70%" });
		gui.add(button);

		// Call the login function when the button is pressed and pass the edit boxes that we created as parameters
		// The "&" in front of "login" can be removed on newer compilers, but is kept here for compatibility with GCC < 8.
		button->onPress(&LoginExample::login, this, editBoxUsername, editBoxPassword);
		return true;
	}
	bool LoginExample::runExample(tgui::GuiBase& gui) {
		try
		{
			if (!loadWidgets(gui))
				return false;
			return true;
		}
		catch (const tgui::Exception& e)
		{
			std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;
			return false;
		}
	}
}