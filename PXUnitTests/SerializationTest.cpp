#include "pch.h"
#include <gtest/gtest.h>
#include "PXFactory/SettingsFactory.h"
#include "PXSerialziation/Serialization.h"
using namespace Settings;
class SerializationTest :public testing::Test {
public:
	ActorSettings actor_settings;
	AnimationSettings animation_settings;
	EngineSettings engine_settings;
	MusicSettings music_settings;
	TextureSettings texture_settings;
	WindowSettings window_settings;
	WorldSettings world_settings;
	virtual void SetUp()override {
		actor_settings.drawable_collision_box = false;
		actor_settings.collision = ActorsEnums::CollisionType::Collision;
		animation_settings.switch_time = 1.0f;
		engine_settings.music_settings_path = "music";
		engine_settings.window_settings_path = "window";
		engine_settings.world_settings_path = "world";
		music_settings.effect_vol = 1.0f;
		music_settings.master_vol = 1.0f;
		texture_settings.texture_path = "texture.texture";
		texture_settings.smooth = false;
		window_settings.fps = 30;
		window_settings.window_name = "window";
		world_settings.gc_frequent_level = 4;
		world_settings.cycle_to_move = 100;
	}
};

TEST_F(SerializationTest, SerializationAndDeserialziationTest) {
	//serialziation
	CREATE_SETTINGS_FILE(actor_settings, "actor_settings.json");
	CREATE_SETTINGS_FILE(animation_settings, "animation_settings.json");
	CREATE_SETTINGS_FILE(engine_settings, "engine_settings.json");
	CREATE_SETTINGS_FILE(music_settings, "music_settings.json");
	CREATE_SETTINGS_FILE(texture_settings, "texture_settings.json");
	CREATE_SETTINGS_FILE(window_settings, "window_settings.json");
	CREATE_SETTINGS_FILE(world_settings, "world_settings.json");
	//deserialization
	auto new_actor_settings = CREATE_SETTINGS(ActorSettings, "actor_settings.json");
	auto new_animation_settings = CREATE_SETTINGS(AnimationSettings, "animation_settings.json");
	auto new_engine_settings = CREATE_SETTINGS(EngineSettings, "engine_settings.json");
	auto new_music_settings = CREATE_SETTINGS(MusicSettings, "music_settings.json");
	auto new_texture_settings = CREATE_SETTINGS(TextureSettings, "texture_settings.json");
	auto new_window_settings = CREATE_SETTINGS(WindowSettings, "window_settings.json");
	auto new_world_settings = CREATE_SETTINGS(WorldSettings, "world_settings.json");
	EXPECT_TRUE(actor_settings == new_actor_settings);
	EXPECT_TRUE(animation_settings == new_animation_settings);
	EXPECT_TRUE(engine_settings == new_engine_settings);
	EXPECT_TRUE(music_settings == new_music_settings);
	EXPECT_TRUE(texture_settings == new_texture_settings);
	EXPECT_TRUE(window_settings == new_window_settings);
	EXPECT_TRUE(world_settings == new_world_settings);
}