#pragma once
#include "PXSettings/ParticleSystemSettings.h"
namespace Factory::ParticleSystemSettings {
	enum class Size {
		small,
		medium,
		big
	};
	Settings::ParticleSystemSettings GetSmokeSettings(const sf::Vector2f& position,Size size);
}