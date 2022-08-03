#include "pch.h"
#include <gtest/gtest.h>
#include "PXFactory/SettingsFactory.h"
#include "PXSerialziation/Serialization.h"
using namespace Settings;
class SerializationTest :public testing::Test {
protected:
	ActorSettings actor_settings;
	AnimationSettings animation_settings;
	EngineSettings engine_settings;
	MusicSettings music_settings;
	TextureSettings texture_settings;
	WindowSettings window_settings;
	WorldSettings world_settings;
public:
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

		world_settings.gc_delay = 4;
		world_settings.deadzone_x = 1500;
	}
};

TEST_F(SerializationTest, SerializationAndDeserialziationTest) {
	//serialziation
	CREATE_SETTINGS_FILE(actor_settings, "cfg\\actor_settings.json");
	CREATE_SETTINGS_FILE(animation_settings, "cfg\\animation_settings.json");
	CREATE_SETTINGS_FILE(engine_settings, "cfg\\engine_settings.json");
	CREATE_SETTINGS_FILE(music_settings, "cfg\\music_settings.json");
	CREATE_SETTINGS_FILE(texture_settings, "cfg\\texture_settings.json");
	CREATE_SETTINGS_FILE(window_settings, "cfg\\window_settings.json");
	CREATE_SETTINGS_FILE(world_settings, "cfg\\world_settings.json");
	//deserialization
	auto new_actor_settings = CREATE_SETTINGS(ActorSettings, "cfg\\actor_settings.json");
	auto new_animation_settings = CREATE_SETTINGS(AnimationSettings, "cfg\\animation_settings.json");
	auto new_engine_settings = CREATE_SETTINGS(EngineSettings, "cfg\\engine_settings.json");
	auto new_music_settings = CREATE_SETTINGS(MusicSettings, "cfg\\music_settings.json");
	auto new_texture_settings = CREATE_SETTINGS(TextureSettings, "cfg\\texture_settings.json");
	auto new_window_settings = CREATE_SETTINGS(WindowSettings, "cfg\\window_settings.json");
	auto new_world_settings = CREATE_SETTINGS(WorldSettings, "cfg\\world_settings.json");
	EXPECT_TRUE(actor_settings == new_actor_settings);
	EXPECT_TRUE(animation_settings == new_animation_settings);
	EXPECT_TRUE(engine_settings == new_engine_settings);
	EXPECT_TRUE(music_settings == new_music_settings);
	EXPECT_TRUE(texture_settings == new_texture_settings);
	EXPECT_TRUE(window_settings == new_window_settings);
	EXPECT_TRUE(world_settings == new_world_settings);
}