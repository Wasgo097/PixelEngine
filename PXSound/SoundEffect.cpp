#include "SoundEffect.h"

namespace Sound {
	SoundEffect::SoundEffect(const sf::SoundBuffer& buffer) :_buffer{ buffer } {
		_sound.setBuffer(_buffer);
	}

	bool SoundEffect::IsValid() const {
		return _buffer.getSampleCount() > 0;
	}
}