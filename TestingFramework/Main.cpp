#include "SerialziationTest.h"
#include <SFML/Graphics.hpp>
using namespace Test;
int main(){
	/*SerialziationTest test1("D:\\PixelEngine\\TestingFramework\\output\\");
	test1.PrepareTest();
	return 0;*/
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while(window.isOpen()){
		sf::Event event;
		while(window.pollEvent(event)){
			if(event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}