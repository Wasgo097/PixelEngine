#pragma once
#include "PXCore/World/WorldBase.h"
namespace Test {
	class MainMenuWorld :public Core::World::WorldBase {
	public:
		virtual void Draw(sf::RenderWindow& window)override;
	protected:
		// Inherited via WorldBase
		virtual void CheckQuit() override {};
	private:
	};
}