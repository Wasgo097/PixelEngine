#include "SoundEffect.h"

namespace Sound {
	SoundEffect::SoundEffect(const sf::SoundBuffer& buffer) :_buffer{ buffer } {
		_sound.setBuffer(_buffer);
	}

	void SoundEffect::SetBuffer(sf::SoundBuffer&& new_buffer) {
		_buffer = std::move(new_buffer);
		_sound.setBuffer(_buffer);
	}

	bool SoundEffect::IsValid() const {
		return _buffer.getSampleCount() > 0 or _sound.getStatus() == sf::SoundSource::Playing;
	}
	void SoundEffect::Play() {
		_sound.play();
	}
	void SoundEffect::Clear() {
		_sound.stop();
	}
	void SoundEffect::SetVolume(float new_volume) {
		_sound.setVolume(100.0 * new_volume);
	}
}