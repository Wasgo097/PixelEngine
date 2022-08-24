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
	class ParticleEmitter;
	class ParticleSystemBase {
	public:
		ParticleSystemBase(ParticleEmitter* parent, const Settings::ParticleSystemSettings& settings);
		void AddParticles(unsigned int particles);
		void Tick(float delta);
		void Draw(sf::RenderWindow& window);
		virtual void InitParticleSystem() {};
		virtual void EndParticleSystem() {};
		virtual bool ToDelete()const;
	protected:
		virtual std::unique_ptr<Particle> CreateParticle()const = 0;
		void Clear();
		void PrepareTexture();
		static const sf::Color _TRANSPARENT;
		static Randomizer  _randomizer;
		ParticleEmitter* _parent;
		Settings::ParticleSystemSettings _settings;
		std::list<std::unique_ptr<Particle>> _particles;
		sf::Image _image; //image->texture->sprite
		sf::Texture _texture;
		sf::Sprite _sprite;
	};
}