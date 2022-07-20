#include "ActorAnimationTest.h"
#include "PXFactory/SettingsFactory.h"
namespace Test {
	bool ActorAnimationTest::PrepareTest()
	{
		//#define PREPARE_SETTINGS
#ifdef PREPARE_SETTINGS
		Settings::ActorSettings main_actor_settings;
		main_actor_settings.collision = ActorsEnums::CollisionType::Collision;
		main_actor_settings.type = ActorsEnums::ActorType::Dynamic;
		main_actor_settings.position = sf::Vector2f(60, 60);
		main_actor_settings.collider_size = sf::Vector2f(64, 64);
		main_actor_settings.tick = true;
		main_actor_settings.drawable_collision_box = false;
		CREATE_SETTINGS_FILE(main_actor_settings, "Cfg\\MainActorSettings.json")
			Settings::TextureSettings main_texture_settings;
		main_texture_settings.texture_path = "Resource\\PixelEngine Base Character\\BaseCharacter.png";
		main_texture_settings.smooth = true;
		main_texture_settings.repeatable = false;
		CREATE_SETTINGS_FILE(main_texture_settings, "Cfg\\MainTextureSettings.json")
			Settings::AnimationSettings main_animation_settings;
		main_animation_settings.rect_size = sf::Vector2u(64, 64);
		main_animation_settings.switch_time = 0.5f;
		//fill MainAnimationMaps
		main_animation_settings.direction_to_row[AnimationEnums::Direction::Up] = 8;
		main_animation_settings.direction_to_row[AnimationEnums::Direction::Left] = 9;
		main_animation_settings.direction_to_row[AnimationEnums::Direction::Down] = 10;
		main_animation_settings.direction_to_row[AnimationEnums::Direction::DownIdle] = 2;
		main_animation_settings.direction_to_row[AnimationEnums::Direction::Right] = 11;
		main_animation_settings.frames_count[2] = 7;
		main_animation_settings.frames_count[8] = 9;
		main_animation_settings.frames_count[9] = 9;
		main_animation_settings.frames_count[10] = 9;
		main_animation_settings.frames_count[11] = 9;
		CREATE_SETTINGS_FILE(main_animation_settings, "Cfg\\MainAnimationSettings.json")
#endif
			return _engine.Run() == 1;
	}

	bool ActorAnimationTest::RunTest()
	{
		try {
			if (PrepareTest())
				return true;
			return false;
		}
		catch (std::exception& ex) {
			std::cout << "std exc " << ex.what() << "\n";
		}
		return false;
	}

}