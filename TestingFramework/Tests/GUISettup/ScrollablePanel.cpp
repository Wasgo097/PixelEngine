#include "ScrollablePanel.h"

namespace Test {
    ScrollablePanel::ScrollablePanel(const ArgumentParser& parser) :BaseTest(parser)
    {
    }
    bool ScrollablePanel::PrepareTest()
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
    bool ScrollablePanel::RunTest()
    {
        try {
            if (PrepareTest())
                return true;
            return false;
        }
        catch (std::exception& ex) {

            std::cerr << "ScrollablePanel exception " << ex.what() << "\n";
        }
        return false;
    }
    bool ScrollablePanel::RunExample(tgui::GuiBase& gui)
    {
        auto panel = tgui::ScrollablePanel::create();
        panel->setPosition(100, 50);
        panel->setSize(400, 500);
        gui.add(panel);

        // Create some pictures to place inside the scrollable panel
        for (unsigned int i = 0; i < 3; ++i)
        {
            auto pic = tgui::Picture::create("Image" + tgui::String(i + 1) + ".png");
            pic->setSize(400, 300);
            pic->setPosition(0, i * 300);
            panel->add(pic);
        }

        // The scrollable area / content size is now 400x900 because of the pictures inside it.
        // If you wish to manually specify the size then you can call the setContentSize function.

        // Hide the horizontal scrollbar. Since the pictures have the same width as the panel,
        // the pictures won't fit inside the panel anymore when the vertical scrollbar is visible.
        // Note that by removing the horizontal scrollbar you won't be able to see the small part
        // of the picture that ends up below the vertical scrollbar.
        panel->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);
        return true;
    }
}