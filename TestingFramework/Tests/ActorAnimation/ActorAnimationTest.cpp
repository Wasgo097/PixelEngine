#include "ActorAnimationTest.h"
#include "Factory/SettingsFactory.h"
namespace Test {
	void ActorAnimationTest::PrepareTest()
	{
//#define PREPARE_SETTINGS
#ifdef PREPARE_SETTINGS
		Settings::ActorSettings MainActorSettings;
		MainActorSettings._collision = ActorsEnums::CollisionType::Collision;
		MainActorSettings._type = ActorsEnums::ActorType::Dynamic;
		MainActorSettings._position = sf::Vector2f(60, 60);
		MainActorSettings._collidersize = sf::Vector2f(60, 60);
		MainActorSettings._tickflag = true;
		CREATE_SETTINGS_FILE("Cfg\\MainActorSettings.json",MainActorSettings)
		Settings::TextureSettings MainTextureSettings;
		MainTextureSettings._texturepath = "C:\\programowanie\\Resource\\PixelEngine Base Character\\BaseCharacter.png";
		MainTextureSettings._smooth = true;
		MainTextureSettings._repeatable = false;
		CREATE_SETTINGS_FILE("Cfg\\MainTextureSettings.json", MainTextureSettings)
		Settings::AnimationSettings MainAnimationSettings;
		MainAnimationSettings._rectsize = sf::Vector2u(60, 60);
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