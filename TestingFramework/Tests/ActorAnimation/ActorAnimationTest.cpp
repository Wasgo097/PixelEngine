#include "ActorAnimationTest.h"
#include "Factory/SettingsFactory.h"
namespace Test {
	void ActorAnimationTest::PrepareTest()
	{
		Settings::ActorSettings MainActorSettings;
		MainActorSettings._collision = ActorsEnums::CollisionType::Collision;
		MainActorSettings._type = ActorsEnums::ActorType::Dynamic;
		MainActorSettings._position = sf::Vector2f(60, 60);
		MainActorSettings._collidersize = sf::Vector2f(60, 60);
		MainActorSettings._tickflag = true;
		Factory::SettingsFactory::CreateSettingsJsonFile("cfg\\MainActorSettings.json",MainActorSettings);
		Settings::TextureSettings MainTextureSettings;
		MainTextureSettings._texturepath = "C:\\programowanie\\Resource\\PixelEngine Base Character\\BaseCharacter.png";
		MainTextureSettings._smooth = true;
		MainTextureSettings._repeatable = false;
		Factory::SettingsFactory::CreateSettingsJsonFile("cfg\\MainTextureSettings.json", MainTextureSettings);
		Settings::AnimationSettings MainAnimationSettings;
		MainAnimationSettings._rectsize = sf::Vector2u(60, 60);
		MainAnimationSettings._switchtime = 0.5f;
		//fill MainAnimationMap
		Factory::SettingsFactory::CreateSettingsJsonFile("cfg\\MainAnimationSettings.json", MainAnimationSettings);
		int result = _engine.Main();
	}

	bool ActorAnimationTest::RunTest()
	{
		try {
			PrepareTest();
			return true;
		}
		catch (std::exception& ex) {
			std::cout << "std exc " << ex.what() << "\n";
		}
		catch (...) {
			return false;
		}
		return false;
	}

}