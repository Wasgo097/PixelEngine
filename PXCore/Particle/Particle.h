#pragma once
#include <functional>
#include <optional>
#include <SFML/Graphics/Image.hpp>
#include "PXSettings/ParticleSettings.h"
namespace Core::Particle {
	class Particle {
	public:
		Particle(const Settings::ParticleSettings& settings, std::optional<std::function<void()>> OnElapsed = {});
		void Tick(float delta, const sf::Vector2f& gravity, float particle_speed, std::optional<unsigned char> dissolution_rate);
		void Draw(sf::Image& image);
		bool ToDelete(const sf::Vector2u& image_size)const;
	protected:
		sf::Vector2f _position;
		sf::Vector2f _velocity;
		sf::Color _color;
		float _time = .0f;
		std::function<void()> OnElapsed;
		const bool _TIMELY = false;
		const float _MAX_TIME = .0f;
	};
}