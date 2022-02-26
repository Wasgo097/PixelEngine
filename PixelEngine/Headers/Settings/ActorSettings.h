#pragma once
#include "SettingsBase.h"
#include "Enums/ActorEnums.h"
#include "Utility/BasicSFMLTypesToJson.h"
namespace Settings {
	class ActorSettings :public SettingsBase {
	public:
		ActorSettings(ActorsEnums::CollisionType collision, ActorsEnums::ActorType type, sf::Vector2f position, sf::Vector2f collidersize, sf::Vector2f velocity, bool tickflag) :
			_collision(collision), _type(type), _position(position), _collidersize(collidersize), _velocity(velocity), _tickflag(tickflag) {}
		ActorSettings() = default;
	public:
		virtual std::string ToStdString()const override;
	public:
		ActorsEnums::CollisionType _collision = ActorsEnums::CollisionType::None;
		ActorsEnums::ActorType _type = ActorsEnums::ActorType::Static;;
		sf::Vector2f _position;
		sf::Vector2f _collidersize;
		sf::Vector2f _velocity;
		bool _tickflag = false;
		bool operator ==(const ActorSettings& obj)const {
			return (_collision == obj._collision) &&
				(_type == obj._type) &&
				(_position == obj._position) &&
				(_collidersize == obj._collidersize) &&
				(_velocity == obj._velocity) &&
				(_tickflag == obj._tickflag);
		}
	};
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ActorSettings, _collision, _type, _position, _collidersize, _velocity, _tickflag)
}