#include "PopUp.h"

namespace Test {
	PopUp::PopUp(const ArgumentParser& parser) :BaseTest(parser)
	{
	}
	bool PopUp::PrepareTest()
	{
        sf::RenderWindow window(sf::VideoMode(800, 600), "TGUI window");
        tgui::GuiSFML gui(window);

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();

                // Check if there is a pop-up menu
                if (_popupMenu)
                {
                    // When mouse is released, remove the pop-up menu
                    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
                    {
                        gui.remove(_popupMenu);
                        _popupMenu = nullptr;
                    }

                    // When mouse is pressed, remove the pop-up menu only when the mouse is not on top of the menu
                    if (event.type == sf::Event::MouseButtonPressed)
                    {
                        if (!_popupMenu->isMouseOnWidget(tgui::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                        {
                            gui.remove(_popupMenu);
                            _popupMenu = nullptr;
                        }
                    }
                }

                // Perhaps we have to open a menu
                else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
                {
                    RightClickCallback(gui, tgui::Vector2f(event.mouseButton.x, event.mouseButton.y));
                }

                gui.handleEvent(event);
            }

            window.clear();
            gui.draw();
            window.display();
        }
		return true;
	}
	bool PopUp::RunTest()
	{
		try {
			if (PrepareTest())
				return true;
			return false;
		}
		catch (std::exception& ex) {

			std::cerr << "PopUp exception " << ex.what() << "\n";
		}
		return false;
	}

    // Called when a right click is detected while popup menu isn't shown

    void PopUp::RightClickCallback(tgui::GuiBase& gui, tgui::Vector2f position)
    {
        _popupMenu = tgui::ListBox::create();
        _popupMenu->addItem("Option 1");
        _popupMenu->addItem("Option 2");
        _popupMenu->addItem("Option 3");
        _popupMenu->addItem("Option 4");
        _popupMenu->setItemHeight(20);
        _popupMenu->setPosition(position);
        _popupMenu->setSize(120, _popupMenu->getItemHeight() * _popupMenu->getItemCount());
        _popupMenu->onItemSelect(&PopUp::PopupMenuCallback,this);
        gui.add(_popupMenu);
    }
    void PopUp::PopupMenuCallback(tgui::String item)
    {
        std::cout << item << std::endl;
    }
}