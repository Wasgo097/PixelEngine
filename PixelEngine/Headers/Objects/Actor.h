#pragma once
#include "Object.h"
#include "CommonHeaders.h"
#include "Settings/ActorSettings.h"
namespace Core{
	class World;
	class Actor :public Object{
	public:
		Actor(World* world, std::optional<std::string> texture_path, const Settings::ActorSettings & settings, sf::Vector2f velocity ) :
			_world(world), _texturepath(texture_path), _settings(settings), _velocity(velocity){}
		bool & TickFlag();
		void Draw(sf::RenderWindow & window);
		void Tick(float deltatime);
	private:
		bool _tickon=false;
		//bool _animationon = false;
	protected:
		std::unique_ptr<sf::Texture> _texture;
		std::unique_ptr<sf::Sprite> _sprite;
		std::optional<sf::RectangleShape> _collider;
		std::optional<std::string> _texturepath;
		Settings::ActorSettings _settings;
		sf::Vector2f _velocity;
		World * _world;
	};
}