#include "Collider.h"
namespace Core::Object::Components {
	Collider::Collider(Core::Object::Actor* parent, const Settings::ActorSettings& actor_settings) :ActorComponentBase(parent), _collider(actor_settings.collider_size) {
		sf::Vector2f temp_origin = _collider.getSize();
		temp_origin.x /= 2.0f;
		//bottom center
		_collider.setOrigin(temp_origin);
		_collider.setPosition(actor_settings.position);
	}
	void Collider::Move(const sf::Vector2f& velocity) {
		_collider.move(velocity);
	}
	const sf::RectangleShape& Collider::GetCollider() const {
		return _collider;
	}
	sf::RectangleShape& Collider::GetCollider() {
		return _collider;
	}
	bool Collider::Collide(const Collider& other) const {
		return _collider.getGlobalBounds().intersects(other._collider.getGlobalBounds());
	}
}