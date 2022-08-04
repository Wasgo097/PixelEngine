#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <vector>
#include <memory>
#include "PXUtilities/Randomizer.h"

enum class Shape {
	circle, 
	square
};
struct Particle
{
	sf::Vector2f pos; // Position
	sf::Vector2f vel; // Velocity
	sf::Color color;  // RGBA
};
class ParticleSystem {
public:
	ParticleSystem(int width, int height);

	void fuel(unsigned int particles); // Adds new particles to m_particles
	void update(); // Updates position, velocity and opacity of all particles
	void render(); // Renders all particles onto m_image
	void clear(); // Removes all particles from m_image

	void setPosition(float x, float y) { _position.x = x; _position.y = y; }
	void setGravity(float x, float y) { _gravity.x = x; _gravity.y = y; }
	void setParticleSpeed(float speed) { _particle_speed = speed; }
	void setDissolve(bool enable) { _dissolve = enable; }
	void setDissolutionRate(unsigned char rate) { _dissolution_rate = rate; }
	void setShape(Shape shape) { _shape = shape; }

	size_t getNumberOfParticles() { return _particles.size(); }
	std::string getNumberOfParticlesString();
	sf::Sprite& getSprite() { return _sprite; }

protected:
	sf::Vector2f _position; // Particle origin (pixel co-ordinates)
	sf::Vector2f _gravity;  // Affects particle velocities
	sf::Clock _clock;    // Used to scale particle motion
	sf::Color _transparent = sf::Color(0, 0, 0, 0);;  // sf::Color( 0, 0, 0, 0 )
	sf::Image _image;    // See render() and remove()
	sf::Texture _texture;
	Randomizer  _randomizer;
	sf::Sprite  _sprite;   // Connected to m_image
	float _particle_speed = 20.0f;// Pixels per second (at most)
	bool _dissolve = false; // Dissolution enabled?
	unsigned char _dissolution_rate = 4;
	Shape _shape = Shape::circle;
	std::vector<std::unique_ptr<Particle>> _particles;
};