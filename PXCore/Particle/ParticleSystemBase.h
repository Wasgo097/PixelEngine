#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#include <memory>
#include "PXUtilities/Randomizer.h"
namespace Core::Particle {
	struct Particle {
		sf::Vector2f pos; // Position
		sf::Vector2f vel; // Velocity
		sf::Color color;  // RGBA
		//ToDo
		//time
		//OnElapsed
	};
	class ParticleSystemBase {
	public:
		//todo parent
		ParticleSystemBase(const sf::Vector2u& size, const sf::Vector2f& position, unsigned int particles);
		void AddParticles(unsigned int particles); // Adds new particles to _particles
		void Update(float delta);
		void Draw(sf::RenderWindow& window);
		virtual void InitParticleSystem() {};
		virtual void EndParticleSystem() {};
	protected:
		virtual std::unique_ptr<Particle> CreateParticle()const = 0;
		void Clear();
		void PrepareTexture();
		static const sf::Color _TRANSPARENT;
		static Randomizer  _randomizer;
		sf::Vector2f _position; // Particle origin
		sf::Vector2f _gravity;  // Affects particle velocities
		sf::Image _image; //image->texture->sprite
		sf::Texture _texture;
		sf::Sprite  _sprite;
		float _particle_speed = 20.0f;
		bool _dissolve = false;
		unsigned char _dissolution_rate = 4;
		std::vector<std::unique_ptr<Particle>> _particles;
	};
}