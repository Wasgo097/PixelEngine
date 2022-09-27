#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include <memory>
#include "PXUtilities/Randomizer.h"
#include "PXSettings/ParticleSystemSettings.h"
#include "Particle.h"
namespace Core::Particle {
	class ParticleSystemBase : public sf::Drawable {
	public:
		ParticleSystemBase(const Settings::ParticleSystemSettings& settings);
		void AddParticles(unsigned int particles);
		virtual void Tick(float delta);
		virtual void InitParticleSystem() {};
		virtual void EndParticleSystem() {};
		virtual bool ToDelete()const;
	protected:
		virtual std::unique_ptr<Particle> CreateParticle(Randomizer& randomizer)const = 0; 
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		std::list<std::unique_ptr<Particle>> CreateParticles(unsigned int particles)const;
		Settings::ParticleSystemSettings _settings;
		std::list<std::unique_ptr<Particle>> _particles;
	};
}