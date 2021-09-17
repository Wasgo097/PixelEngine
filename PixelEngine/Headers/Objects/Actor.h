#pragma once
#include "Object.h"
#include "CommonHeaders.h"
namespace Core{
	class Actor :public Object{
	public:
		virtual void Init(){}
		virtual void Tick(double time){}
		virtual void OnLoad(){}
		virtual void OnSpawn(){}
	protected:
		std::unique_ptr<sf::Texture> _texture;
		std::unique_ptr<sf::Sprite> _sprite;
	};
}
