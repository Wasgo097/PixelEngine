#pragma once
#include "Object.h"
#include "Settings/ActorSettings.h"
#include "Settings/TextureSettings.h"
#include <SFML/Graphics.hpp>
#include <optional>
namespace Object {
	class WorldBase;
	class Actor :public Object{
	public:
		Actor(WorldBase* world, const Settings::ActorSettings & actor_settings,const Settings::TextureSettings& texture_settings);
		Actor(const Actor &) = delete;
		Actor & operator=(const Actor &) = delete;
		Actor(Actor &&) = delete;;
		Actor& operator=(Actor&&) = delete;;
		virtual ~Actor()=default;

		bool TickFlag()const;
		void SetTickFlag(bool flag);
		bool CanCollide()const;
		const sf::RectangleShape &GetCollider()const;
		void SetWorld(WorldBase* world_ptr);
	public:
		virtual void Tick(float delta_time);
		virtual void Move(const sf::Vector2f& velocity);
		virtual void ConstPush(const sf::Vector2f& const_velocity);
		virtual void Draw(sf::RenderWindow & window);

		virtual std::string ToString()const override;
	private:
		bool _tick=false;
	protected:
		WorldBase* _world;
		std::unique_ptr<sf::Texture> _texture;
		std::unique_ptr<sf::Sprite> _sprite;
		std::optional<sf::RectangleShape> _collider;
		Settings::ActorSettings _actor_settings;
		Settings::TextureSettings _texture_settings;
		sf::Vector2f _velocity;
		bool _pushed = false;
	};
}