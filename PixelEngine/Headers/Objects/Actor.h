#pragma once
#include "Object.h"
#include "Settings/ActorSettings.h"
namespace Core{
	class World;
	class Actor :public Object{
	public:
		Actor(World* world, const Settings::ActorSettings & settings);
		Actor(const Actor &) = delete;
		Actor & operator=(const Actor &) = delete;
		Actor(Actor &&) = delete;;
		Actor& operator=(Actor&&) = delete;;
		virtual ~Actor();
	public:
		bool & TickFlag();
		bool CanCollide()const;
		const sf::RectangleShape &GetCollider()const;
	public:
		virtual void Tick(float deltatime);
		virtual void Move(const sf::Vector2f& velocity);
		virtual void Push(const sf::Vector2f& constvelocity);
		virtual void Draw(sf::RenderWindow & window);
		virtual std::string ToString()const override;
	private:
		bool _tickon=false;
	protected:
		World * _world;
		std::unique_ptr<sf::Texture> _texture;
		std::unique_ptr<sf::Sprite> _sprite;
		std::optional<sf::RectangleShape> _collider;
		Settings::ActorSettings _settings;
		sf::Vector2f _velocity;
		bool _pushed = false;
	};
}