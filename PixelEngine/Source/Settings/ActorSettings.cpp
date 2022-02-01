#include "Settings/ActorSettings.h"
#include <sstream>
namespace Settings{
	ActorSettings::ActorSettings(CollisionType collision, ActorType type, sf::Vector2f position, sf::Vector2f collidersize, sf::Vector2f velocity, bool tickflag, TextureSettings texturesettings) :
		_collision(collision), _type(type), _position(position), _collidersize(collidersize), _velocity(velocity), _tickflag(tickflag), _texture(texturesettings){}

	std::string ActorSettings::ToStdString() const{
		std::stringstream stream;
		stream << "Collision Type: " << static_cast<int>(_collision) << " Actor Type: " << static_cast<int>(_type) << "Location " << _position.x << " " << _position.y <<
			" Collider Size: " << _collidersize.x << " " << _collidersize.y << " Velocity: " << _velocity.x << " " << _velocity.y << " Tick Flag: " << _tickflag;
		return stream.str();
	}

	json ActorSettings::JSerialize() const{
		try{
			json output;
			output["_collision"] = static_cast<int>(_collision);
			output["_type"] = static_cast<int>(_type);
			output["_positionx"] = _position.x;
			output["_positiony"] = _position.y;
			output["_collidersizex"] = _collidersize.x;
			output["_collidersizey"] = _collidersize.y;
			output["_velocityx"] = _velocity.x;
			output["_velocityy"] = _velocity.y;
			output["_tickflag"] = _tickflag;
			//todo texture settings
			return output;
		}
		catch(...){
			return json();
		}
	}

	bool ActorSettings::JDeserialize(json json){
		try{
			_collision = static_cast<CollisionType>(json["_collision"]);
			_type = static_cast<ActorType>(json["_type"]);
			_position.x = json["_positionx"];
			_position.y = json["_positiony"];
			_collidersize.x = json["_collidersizex"];
			_collidersize.y = json["_collidersizey"];
			_velocity.x = json["_velocityx"];
			_velocity.y = json["_velocityy"];
			_tickflag = json["_tickflag"];
			//todo texture settings
			return true;
		}
		catch(...){
			return false;
		}
	}

	const CollisionType & ActorSettings::GetCollision() const{
		return _collision;
	}

	const ActorType & ActorSettings::GetActorType() const{
		return _type;
	}

	const sf::Vector2f & ActorSettings::GetPosition() const{
		return _position;
	}

	const sf::Vector2f & ActorSettings::GetColliderSize() const{
		return _collidersize;
	}

	const sf::Vector2f & ActorSettings::GetVelocity() const{
		return _velocity;
	}

	bool ActorSettings::GetTickFlag() const{
		return _tickflag;
	}

	const TextureSettings & ActorSettings::GetTextureSettings() const{
		return _texture;
	}
}