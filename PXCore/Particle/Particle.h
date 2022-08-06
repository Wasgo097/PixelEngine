#pragma once
#include <functional>
#include <optional>
#include <SFML/Graphics/Image.hpp>
#include "PXSettings/ParticleSettings.h"
namespace Core::Particle {
	struct Particle {
		Particle(const Settings::ParticleSettings& settings, std::optional<std::function<void()>> OnElapsed);
		void Tick(float delta, const sf::Vector2f& gravity, float particle_speed, std::optional<unsigned char> dissolution_rate);
		void Draw(sf::Image& image);
		bool IsValid(const sf::Vector2u& image_size)const;
	protected:
		sf::Vector2f position;
		sf::Vector2f velocity;
		sf::Color color;
		bool timely = false;
		float time = .0f;
		const float max_time = .0f;
		std::function<void()> OnElapsed;
	};
}