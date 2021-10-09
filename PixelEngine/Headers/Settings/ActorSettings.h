#pragma once
#include "SettingsBase.h"
#include "TextureSettings.h"
#include "Utility/ISerializable.h"
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
	class ActorSettings :public SettingsBase,Utility::IJsonSerializable{
	public:
		ActorSettings(CollisionType collision,ActorType type, sf::Vector2f position,sf::Vector2f collidersize, sf::Vector2f velocity,bool tickflag, BaseTextureSettings texturesettings):
			_collision(collision),_type(type),_position(position),_collidersize(collidersize),_velocity(velocity),_tickflag(tickflag),_texture(texturesettings){}
		ActorSettings() = default;
		virtual std::string ToStdString()const override{
			std::stringstream stream;
			stream << "Collision Type: " << static_cast<int>(_collision) << " Actor Type: " << static_cast<int>(_type) << "Location " << _position.x << " " << _position.y <<
				" Collider Size: " << _collidersize.x << " " << _collidersize.y << " Velocity: " << _velocity.x << " " << _velocity.y << " Tick Flag: " << _tickflag;
			return stream.str();
		}
		virtual json JSerialize()const override{
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
		virtual bool JDeserialize(json json)override{
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
		const CollisionType& GetCollision()const{
			return _collision;
		}
		const ActorType& GetActorType()const{
			return _type;
		}
		const sf::Vector2f & GetPosition()const{
			return _position;
		}
		const sf::Vector2f & GetColliderSize()const{
			return _collidersize;
		}
		const sf::Vector2f& GetVelocity()const{
			return _velocity;
		}
		bool GetTickFlag()const{
			return _tickflag;
		}
		const BaseTextureSettings & GetTextureSettings()const{
			return _texture;
		}
	protected:
		CollisionType _collision=CollisionType::None;
		ActorType _type = ActorType::Static;;
		sf::Vector2f _position = sf::Vector2f(.0f, .0f);
		sf::Vector2f _collidersize = sf::Vector2f(.0f, .0f);
		sf::Vector2f _velocity = sf::Vector2f(.0f, .0f);
		bool _tickflag=false;
		BaseTextureSettings _texture;
	};
}