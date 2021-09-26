#pragma once
#include "Object.h"
#include "CommonHeaders.h"
#include "Settings/ActorSettings.h"
namespace Core{
	class World;
	class Actor :public Object{
	public:
		Actor(World* world, const Settings::ActorSettings & settings);
		Actor(const Actor &) = delete;
		Actor & operator=(const Actor &) = delete;
		Actor(Actor &&) = default;
		Actor& operator=(Actor&&) = default;
		virtual ~Actor();
		bool & TickFlag();
		void Draw(sf::RenderWindow & window);
		void Tick(float deltatime);
		bool CanCollide()const;
		const sf::RectangleShape &GetCollider()const;
		void Move(const sf::Vector2f& velocity);
	private:
		bool _tickon=false;
	protected:
		World * _world;
		std::unique_ptr<sf::Texture> _texture;
		std::unique_ptr<sf::Sprite> _sprite;
		std::optional<sf::RectangleShape> _collider;
		Settings::ActorSettings _settings;
		sf::Vector2f _velocity;
	};
}