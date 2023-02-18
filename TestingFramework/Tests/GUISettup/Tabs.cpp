#include "Tabs.h"

namespace Test {
    Tabs::Tabs(const ArgumentParser& parser) :BaseTest(parser)
    {
    }
    bool Tabs::PrepareTest()
    {
        //sf::RenderWindow window(sf::VideoMode(800, 600), "TGUI window");
        //tgui::Gui gui(window);
        //if (!RunExample(gui)) {
        //    return false;
        //}
        //while (window.isOpen()) {
        //    sf::Event event;
        //    while (window.pollEvent(event)) {
        //        gui.handleEvent(event);

        //        if (event.type == sf::Event::Closed)
        //            window.close();
        //    }

        //    window.clear();
        //    gui.draw();
        //    window.display();
        //}
        //return true;
        return false;
    }
    bool Tabs::RunTest()
    {
        try {
            if (PrepareTest())
                return true;
            return false;
        }
        catch (std::exception& ex) {

            std::cerr << "Tabs exception " << ex.what() << "\n";
        }
        return false;
    }
}