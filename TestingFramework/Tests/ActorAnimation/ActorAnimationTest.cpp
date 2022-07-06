#include "ActorAnimationTest.h"
#include "PXFactory/SettingsFactory.h"
namespace Test {
	void ActorAnimationTest::PrepareTest()
	{
//#define PREPARE_SETTINGS
#ifdef PREPARE_SETTINGS
		Settings::ActorSettings MainActorSettings;
		MainActorSettings.CollisionType = ActorsEnums::CollisionType::Collision;
		MainActorSettings.ActorType = ActorsEnums::ActorType::Dynamic;
		MainActorSettings.Position = sf::Vector2f(60, 60);
		MainActorSettings.ColliderSize = sf::Vector2f(64, 64);
		MainActorSettings.TickFlag = true;
		MainActorSettings.DrawableCollisionBox = false;
		CREATE_SETTINGS_FILE("Cfg\\MainActorSettings.json",MainActorSettings)
		Settings::TextureSettings MainTextureSettings;
		MainTextureSettings._texturepath = "Resource\\PixelEngine Base Character\\BaseCharacter.png";
		MainTextureSettings._smooth = true;
		MainTextureSettings._repeatable = false;
		CREATE_SETTINGS_FILE("Cfg\\MainTextureSettings.json", MainTextureSettings)
		Settings::AnimationSettings MainAnimationSettings;
		MainAnimationSettings._rectsize = sf::Vector2u(64, 64);
		MainAnimationSettings._switchtime = 0.5f;
		//fill MainAnimationMaps
		MainAnimationSettings._directiontorow[AnimationEnums::Direction::Up] = 8;
		MainAnimationSettings._directiontorow[AnimationEnums::Direction::Left] = 9;
		MainAnimationSettings._directiontorow[AnimationEnums::Direction::Down] = 10;
		MainAnimationSettings._directiontorow[AnimationEnums::Direction::DownIdle] = 2;
		MainAnimationSettings._directiontorow[AnimationEnums::Direction::Right] = 11;		
		MainAnimationSettings._framescount[2] = 7;
		MainAnimationSettings._framescount[8] = 9;
		MainAnimationSettings._framescount[9] = 9;
		MainAnimationSettings._framescount[10] = 9;
		MainAnimationSettings._framescount[11] = 9;
		CREATE_SETTINGS_FILE("Cfg\\MainAnimationSettings.json", MainAnimationSettings)
#endif
		int result = _engine.Run();
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
		return false;
	}

}