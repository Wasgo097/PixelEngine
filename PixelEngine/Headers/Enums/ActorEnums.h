#pragma once
#include "json.hpp"
namespace ActorsEnums {
	enum class CollisionType {
		None,
		Overlap,
		Collision
	};
	enum class ActorType {
		Static,
		Dynamic
	};
	NLOHMANN_JSON_SERIALIZE_ENUM(CollisionType, {
	{CollisionType::None, "None"},
	{CollisionType::Overlap, "Overlap"},
	{CollisionType::Collision, "Collision"}
		})
	NLOHMANN_JSON_SERIALIZE_ENUM(ActorType, {
	{ActorType::Static, "Static"},
	{ActorType::Dynamic, "Dynamic"}
		})
}