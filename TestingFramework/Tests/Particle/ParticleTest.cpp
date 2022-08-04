#include "ParticleTest.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include "ParticleSystem.h"
namespace Test {
	ParticleTest::ParticleTest(const ArgumentParser& parser) :BaseTest(parser) {
	}
	bool ParticleTest::PrepareTest() {
        int width = 640;
        int height = 480;

        sf::RenderWindow window(sf::VideoMode(width, height, 32), "Inside the Particle Storm");
        window.setVerticalSyncEnabled(true);
        window.setFramerateLimit(0);
        //const sf::Input& input = window.getInput();
        sf::Event events;
        sf::Font font;
        if (!font.loadFromFile("Resource\\test_font.ttf")) return false;
        sf::Text text("", font, 10);
        text.setPosition(10.0f, 10.0f);

        ParticleSystem particleSystem(width, height);
        //particleSystem.setPosition( width/2, height/2 );
        //particleSystem.setGravity( 1.0f, 1.0f );
        //particleSystem.setParticleSpeed( 80.0f );
        particleSystem.setDissolve(true);
        particleSystem.setDissolutionRate(1);
        particleSystem.setShape(Shape::circle);

        particleSystem.fuel(1000);

        float xpos = 320.0f;
        float ypos = 240.0f;
        float xgrv = 0.0f;
        float ygrv = 0.0f;
        sf::Clock clock;
        while (window.isOpen())
        {
            while (window.pollEvent(events))
                switch (events.type) {
                case sf::Event::Closed:
                    window.close(); break;
                case sf::Event::KeyPressed:
                    if (events.key.code == sf::Keyboard::Escape)
                        window.close();
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                        particleSystem.fuel(1000/* * window.getFrameTime() */);
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                        particleSystem.setPosition(--xpos, ypos);
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                        particleSystem.setPosition(++xpos, ypos);
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                        particleSystem.setPosition(xpos, --ypos);
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                        particleSystem.setPosition(xpos, ++ypos);
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                        particleSystem.setGravity(--xgrv * 0.1f, ygrv * 0.1f);
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                        particleSystem.setGravity(++xgrv * 0.1f, ygrv * 0.1f);
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                        particleSystem.setGravity(xgrv * 0.1f, --ygrv * 0.1f);
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                        particleSystem.setGravity(xgrv * 0.1f, ++ygrv * 0.1f);
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
                        particleSystem.setGravity(0.0f, 0.0f);
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
                        particleSystem.setPosition(320.0f, 240.0f);
                    break;
                }

            particleSystem.clear();
            particleSystem.update();
            particleSystem.render();

            text.setString(particleSystem.getNumberOfParticlesString());
            window.clear(sf::Color::Black);
            window.draw(particleSystem.getSprite());
            window.draw(text);
            window.display();
        }

        return true;
	}
	bool ParticleTest::RunTest() {
		try {
			if (PrepareTest())
				return true;
			return false;
		}
		catch (std::exception& ex) {
			std::cerr << "ParticleTest exception " << ex.what() << "\n";
		}
		return false;
	}
}