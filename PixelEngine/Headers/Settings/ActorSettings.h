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
		ActorSettings(CollisionType collision,ActorType type, sf::Vector2f location,sf::Vector2f collidersize,bool tickflag,TextureSettings texture):
			_collision(collision),_type(type),_location(location),_collidersize(collidersize),_tickflag(tickflag),_texture(texture){}
		ActorSettings() = default;
		// Inherited via SettingsBase
		virtual std::string ToStdString() override{
			return "Collision Type: " + std::to_string(static_cast<int>(_collision)) + " Actor Type: " + std::to_string(static_cast<int>(_type)) + "LOcation "+std::to_string(_location.x)+" "+std::to_string(_location.y)+
				" Collider Size: " + std::to_string(_collidersize.x) + " " + std::to_string(_collidersize.y) + " Tick Flag: " + std::to_string(_tickflag);
		}
		const CollisionType& GetCollision()const{
			return _collision;
		}
		const ActorType& GetActorType()const{
			return _type;
		}
		const sf::Vector2f & GetColliderSize()const{
			return _collidersize;
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
		sf::Vector2f _location = sf::Vector2f(.0f, .0f);
		sf::Vector2f _collidersize = sf::Vector2f(.0f, .0f);
		bool _tickflag=false;
		TextureSettings _texture;
	};
}