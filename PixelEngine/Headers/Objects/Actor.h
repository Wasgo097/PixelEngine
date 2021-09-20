#pragma once
#include "Object.h"
#include "CommonHeaders.h"
namespace Core{
	class Actor :public Object{
	public:
		/*Actor(const std::string& texture_path){}
		Actor(std::string&& texture_path){}*/
		bool & TickFlag();
		void Draw(sf::RenderWindow & window);
		void Tick(double time);
	private:
		bool _tickon=false;
		bool _animationon = false;
	protected:
		std::unique_ptr<sf::Texture> _texture;
		std::unique_ptr<sf::Sprite> _sprite;
		std::string _texturepath;
	};
}
