#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
namespace Core {
	class LevelBase {
	public:
		LevelBase();
		virtual ~LevelBase();
	protected:
		bool _quit = false;
	public:
		virtual void Draw(sf::RenderWindow& window) = 0;
		virtual void Update(float delta);
		virtual bool ToQuit()const;
	protected:
		virtual void CheckQuit() = 0;
		virtual void InitLevel() = 0;
		virtual void EndLevel() = 0;
	};
}