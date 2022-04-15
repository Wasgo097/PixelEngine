#pragma once
#include "Object.h"
#include "Settings/ActorSettings.h"
#include "Settings/TextureSettings.h"
#include <SFML/Graphics.hpp>
#include <optional>
namespace Core{
	class WorldBase;
	class Actor :public Object{
	public:
		Actor(WorldBase* world, const Settings::ActorSettings & actorsettings,const Settings::TextureSettings& texturesettings);
		Actor(const Actor &) = delete;
		Actor & operator=(const Actor &) = delete;
		Actor(Actor &&) = delete;;
		Actor& operator=(Actor&&) = delete;;
		virtual ~Actor()=default;
	public:
		bool TickFlag()const;
		void SetTickFlag(bool Flag);
		bool CanCollide()const;
		const sf::RectangleShape &GetCollider()const;
		void SetWorld(WorldBase* worldptr);
	public:
		virtual void Tick(float deltatime);
		virtual void Move(const sf::Vector2f& velocity);
		virtual void ConstPush(const sf::Vector2f& constvelocity);
		virtual void Draw(sf::RenderWindow & window);
	public:
		virtual void Init()override{}
		virtual void OnLoad()override{}
		virtual void OnSpawn()override{}
		virtual void OnDelete()override{}
		virtual std::string ToString()const override;
	private:
		bool _tickon=false;
	protected:
		WorldBase* _world;
		std::unique_ptr<sf::Texture> _texture;
		std::unique_ptr<sf::Sprite> _sprite;
		std::optional<sf::RectangleShape> _collider;
		Settings::ActorSettings _actorsettings;
		Settings::TextureSettings _texturesettings;
		sf::Vector2f _velocity;
		bool _pushed = false;
	};
}