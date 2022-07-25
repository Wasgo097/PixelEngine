#pragma once
#include "ActorComponentBase.h"
#include "PXSettings/ActorSettings.h"
#include <SFML/Graphics/RectangleShape.hpp>
namespace Core::Object::Components {
	class Collider :public ActorComponentBase {
	public:
		Collider(Core::Object::Actor* parent, const Settings::ActorSettings& actor_settings);
		// Inherited via ActorComponentBase
		virtual void Tick(float delta_time) override {};
		void Move(const sf::Vector2f& velocity);
		const sf::RectangleShape& GetCollider()const;
		sf::RectangleShape& GetCollider();
		bool Collide(const Collider& other,sf::FloatRect& out_rect)const;		
	protected:
		sf::RectangleShape _collider;
	};
}