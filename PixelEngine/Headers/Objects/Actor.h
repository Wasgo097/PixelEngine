#pragma once
#include "Object.h"
#include "CommonHeaders.h"
#include "Settings/ActorSettings.h"
namespace Core{
	class Actor :public Object{
	public:
		Actor(const std::string& texture_path,const Settings::ActorSettings & settings,sf::Vector2f velocity=sf::Vector2f(.0f,.0f)):_texturepath(texture_path),_settings(settings),_velocity(velocity){}
		bool & TickFlag();
		void Draw(sf::RenderWindow & window);
		void Tick(float deltatime);
	private:
		bool _tickon=false;
		bool _animationon = false;
	protected:
		std::unique_ptr<sf::Texture> _texture;
		std::unique_ptr<sf::Sprite> _sprite;
		std::string _texturepath;
		Settings::ActorSettings _settings;
		sf::Vector2f _velocity;
	};
}
