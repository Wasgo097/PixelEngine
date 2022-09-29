#pragma once
#include "PXUtilities/Interfaces/ISongManager.h"
namespace Sound {
	class SoundsManager :public ISongManager {
	public:
		// Inherited via ISongManager
		virtual void PlayAll() override;

		virtual void StopAll() override;

		virtual void SetVolume(double new_volume) override;

		virtual void Clear() override;

		virtual void PlayNearbySong(const sf::Vector2f& position) override;

	};
}