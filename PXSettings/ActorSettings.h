#pragma once
#include "PXUtilities/Enums/ActorEnums.h"
#include <SFML/System/Vector2.hpp>
namespace Settings {
	struct ActorSettings{
		ActorSettings(ActorsEnums::CollisionType collision, ActorsEnums::ActorType type, sf::Vector2f position, sf::Vector2f collider_size, sf::Vector2f velocity, bool tick) :
			collision{ collision }, type{ type }, position{ position }, collider_size{ collider_size }, velocity{ velocity }, tick{ tick } {}
		ActorSettings() = default;

		bool operator ==(const ActorSettings& obj)const {
			return (collision == obj.collision) &&
				(type == obj.type) &&
				(position == obj.position) &&
				(collider_size == obj.collider_size) &&
				(velocity == obj.velocity) &&
				(tick == obj.tick) &&
				(drawable_collision_box == obj.drawable_collision_box);
		}

		ActorsEnums::CollisionType collision = ActorsEnums::CollisionType::None;
		ActorsEnums::ActorType type = ActorsEnums::ActorType::Static;;
		sf::Vector2f position;
		sf::Vector2f collider_size;
		sf::Vector2f velocity;
		bool tick = false;
		bool drawable_collision_box = false;

	};
}