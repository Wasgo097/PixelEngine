#include "MyParticleTest.h"
#include "PXCore/Particle/ParticleEmitter.h"
#include "ExampleParticleSystem.h"
#include <SFML/Graphics.hpp>
using namespace Core::Particle;
namespace Test {
	bool MyParticleTest::PrepareTest() {
		sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");
		ParticleEmitter emiter(nullptr);
		Settings::ParticleSystemSettings settings;
		settings.dissolution_rate = 0;
		settings.dissolve = false;
		settings.gravity = sf::Vector2f{ .0f,.0f };
		settings.particle_speed = .0f;
		settings.position = sf::Vector2f{ 300.0f,300.0f };
		settings.size = sf::Vector2u{ 100,100 };
		emiter.PushNewParticles(std::make_unique<ExampleParticleSystem>(&emiter, settings));
		while (window.isOpen()) {
			sf::Event action;
			while (window.pollEvent(action)) {
				if (action.type == sf::Event::Closed)
					window.close();
			}
			emiter.Tick(0.001);
			window.clear();
			emiter.Draw(window);
			window.display();
		}
		return true;
	}
	bool MyParticleTest::RunTest() {
		try {
			if (PrepareTest())
				return true;
			return false;
		}
		catch (std::exception& ex) {
			std::cerr << "MyParticleTest exception " << ex.what() << "\n";
		}
		return false;
	}
}