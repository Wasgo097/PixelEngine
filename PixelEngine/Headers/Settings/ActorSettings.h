#pragma once
#include "SettingsBase.h"
#include "TextureSettings.h"
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
		ActorSettings(CollisionType collision,ActorType type, sf::Vector2f position,sf::Vector2f collidersize, sf::Vector2f velocity,bool tickflag,TextureSettings texturesettings):
			_collision(collision),_type(type),_position(position),_collidersize(collidersize),_velocity(velocity),_tickflag(tickflag),_texture(texturesettings){}
		ActorSettings() = default;
		// Inherited via SettingsBase
		virtual std::string ToStdString() override{
			std::stringstream stream;
			stream<< "Collision Type: " << static_cast<int>(_collision) << " Actor Type: " << static_cast<int>(_type) << "Location "<<_position.x<<" "<<_position.y<<
				" Collider Size: " << _collidersize.x << " " <<_collidersize.y <<" Velocity: "<<_velocity.x<<" "<<_velocity.y<< " Tick Flag: " <<_tickflag;
			return stream.str();
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
		const TextureSettings & GetTextureSettings()const{
			return _texture;
		}
	protected:
		CollisionType _collision=CollisionType::None;
		ActorType _type = ActorType::Static;;
		sf::Vector2f _position = sf::Vector2f(.0f, .0f);
		sf::Vector2f _collidersize = sf::Vector2f(.0f, .0f);
		sf::Vector2f _velocity = sf::Vector2f(.0f, .0f);
		bool _tickflag=false;
		TextureSettings _texture;
	};
}