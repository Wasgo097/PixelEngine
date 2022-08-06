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
#include "PXSettings/ParticleSystemSettings.h"
#include "Particle.h"
namespace Core::Particle {
	class ParticleSystemBase {
	public:
		//todo parent
		ParticleSystemBase(const Settings::ParticleSystemSettings& settings, unsigned int particles);
		void AddParticles(unsigned int particles);
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
		Settings::ParticleSystemSettings _settings;
		sf::Image _image; //image->texture->sprite
		sf::Texture _texture;
		sf::Sprite  _sprite;
		std::vector<std::unique_ptr<Particle>> _particles;
	};
}