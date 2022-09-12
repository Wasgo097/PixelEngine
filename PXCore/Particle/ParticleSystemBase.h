#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#include <list>
#include <memory>
#include "PXUtilities/Randomizer.h"
#include "PXSettings/ParticleSystemSettings.h"
#include "Particle.h"
namespace Core::Particle {
	class ParticleSystemBase {
	public:
		ParticleSystemBase(const Settings::ParticleSystemSettings& settings);
		void AddParticles(unsigned int particles);
		void Tick(float delta);
		void Draw(sf::RenderWindow& window);
		virtual void InitParticleSystem() {};
		virtual void EndParticleSystem() {};
		virtual bool ToDelete()const;
	protected:
		virtual std::unique_ptr<Particle> CreateParticle(Randomizer& randomizer)const = 0;
		void Clear();
		void PrepareTexture();
		std::list<std::unique_ptr<Particle>> CreateParticles(unsigned int particles)const;
		static const sf::Color _TRANSPARENT;
		Settings::ParticleSystemSettings _settings;
		std::list<std::unique_ptr<Particle>> _particles;
		sf::Image _image; //image->texture->sprite
		sf::Texture _texture;
		sf::Sprite _sprite;
	};
}