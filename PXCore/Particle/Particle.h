#pragma once
#include <functional>
#include <optional>
#include <SFML/Graphics.hpp>
#include "PXSettings/ParticleSettings.h"
namespace Core::Particle {
	class Particle :public sf::Drawable {
	public:
		Particle(const Settings::ParticleSettings& settings, std::optional<std::function<void()>> OnElapsed = {});
		void Tick(float delta, const sf::Vector2f& gravity, float particle_speed, std::optional<unsigned char> dissolution_rate);
		bool ToDelete(const sf::FloatRect& range) const;
	protected:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		sf::Vertex _vertex;
		sf::Vector2f _velocity;
		float _time{ .0f };
		float _current_dissolution{ .0f };
		std::function<void()> OnElapsed;
		const bool _TIMELY = false;
		const float _MAX_TIME = { .0f };
	};
}