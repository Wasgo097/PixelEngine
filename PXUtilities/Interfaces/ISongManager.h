#pragma once
#include <SFML/System/Vector2.hpp>
class ISongManager {
public:
	virtual void PlayAll() = 0;
	virtual void StopAll() = 0;
	virtual void SetVolume(double new_volume) = 0;
	virtual void Clear() = 0;
	virtual void PlayNearbySong(const sf::Vector2f& position) = 0;
};