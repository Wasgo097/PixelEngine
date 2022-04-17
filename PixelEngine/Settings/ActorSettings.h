#pragma once
#include "SettingsBase.h"
#include "Enums/ActorEnums.h"
#include "Utility/BasicSFMLTypesToJson.h"
namespace Settings {
	class ActorSettings :public SettingsBase {
	public:
		ActorSettings(ActorsEnums::CollisionType collision, ActorsEnums::ActorType type, sf::Vector2f position, sf::Vector2f collidersize, sf::Vector2f velocity, bool tickflag) :
			CollisionType(collision), ActorType(type), Position(position), ColliderSize(collidersize), Velocity(velocity), TickFlag(tickflag) {}
		ActorSettings() = default;
	public:
		virtual std::string ToStdString()const override;
	public:
		ActorsEnums::CollisionType CollisionType = ActorsEnums::CollisionType::None;
		ActorsEnums::ActorType ActorType = ActorsEnums::ActorType::Static;;
		sf::Vector2f Position;
		sf::Vector2f ColliderSize;
		sf::Vector2f Velocity;
		bool TickFlag = false;
		bool DrawableCollisionBox = false;
		bool operator ==(const ActorSettings& obj)const {
			return (CollisionType == obj.CollisionType) &&
				(ActorType == obj.ActorType) &&
				(Position == obj.Position) &&
				(ColliderSize == obj.ColliderSize) &&
				(Velocity == obj.Velocity) &&
				(TickFlag == obj.TickFlag) &&
				(DrawableCollisionBox == obj.DrawableCollisionBox);
		}
	};
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ActorSettings, CollisionType, ActorType, Position, ColliderSize, Velocity, TickFlag, DrawableCollisionBox)
}