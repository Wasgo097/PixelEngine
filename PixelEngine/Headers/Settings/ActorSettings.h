#pragma once
//base
#include "SettingsBase.h"
#include "Utility/ISerializable.h"

#include "TextureSettings.h"
#include <sfml/System.hpp>
using nlohmann::json;
namespace Settings{
	class TextureSettings;
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
		ActorSettings(CollisionType collision, ActorType type, sf::Vector2f position, sf::Vector2f collidersize, sf::Vector2f velocity, bool tickflag, TextureSettings texturesettings);
		ActorSettings() = default;
	public:
		virtual std::string ToStdString()const override;
		virtual json JSerialize()const override;
		virtual bool JDeserialize(json json)override;
	public:
		const CollisionType& GetCollision()const;
		const ActorType& GetActorType()const;
		const sf::Vector2f & GetPosition()const;
		const sf::Vector2f & GetColliderSize()const;
		const sf::Vector2f& GetVelocity()const;
		bool GetTickFlag()const;
		const TextureSettings & GetTextureSettings()const;
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