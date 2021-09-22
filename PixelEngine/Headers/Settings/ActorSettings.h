#pragma once
#include "SettingsBase.h"
namespace Settings{
	enum class CollisionType{
		None,
		Overlap,
		Collision
	};
	enum class ActorType{
		Static,
		Dynamic
	};
	class ActorSettings :public SettingsBase{
	public:
		ActorSettings(CollisionType collision,ActorType type):_collision(collision),_type(type){}
		// Inherited via SettingsBase
		virtual std::string ToStdString() override{
			return "Collision Type: " + std::to_string(static_cast<int>(_collision)) + " Actor Type: " + std::to_string(static_cast<int>(_type));
		}
		const CollisionType& GetCollision()const{
			return _collision;
		}
		const ActorType& GetActorType()const{
			return _type;
		}
	protected:
		CollisionType _collision;
		ActorType _type;
	};
}