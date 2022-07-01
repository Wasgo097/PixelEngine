#pragma once
#include "BasicSFMLTypesToJson.h"
#include "Enums/ActorEnums.h"
#include "Enums/AnimationEnums.h"
#include "Enums/InputEnums.h"

#include "Settings/ActorSettings.h"
#include "Settings/AnimationSettings.h"
#include "Settings/EngineSettings.h"
#include "Settings/MusicSettings.h"
#include "Settings/TextureSettings.h"
#include "Settings/WindowSettings.h"
#include "Settings/WorldSettings.h"
namespace ActorsEnums {

NLOHMANN_JSON_SERIALIZE_ENUM(CollisionType, {
	{CollisionType::None, "None"},
	{CollisionType::Overlap, "Overlap"},
	{CollisionType::Collision, "Collision"}
		})
		NLOHMANN_JSON_SERIALIZE_ENUM(ActorType, {
		{ActorType::Static, "Static"},
		{ActorType::Dynamic, "Dynamic"}
			})
}

namespace AnimationEnums {
	NLOHMANN_JSON_SERIALIZE_ENUM(Direction, {
	{Direction::None, "None"},
	{Direction::Left, "Left"},
	{Direction::Up, "Up"},
	{Direction::Right, "Right"},
	{Direction::Down, "Down"},
	{Direction::LeftIdle, "LeftIdle"},
	{Direction::UpIdle, "UpIdle"},
	{Direction::RightIdle, "RightIdle"},
	{Direction::DownIdle, "DownIdle"}
		})
}
namespace Controller {
	NLOHMANN_JSON_SERIALIZE_ENUM(InputType, {
	{InputType::KeyboardInput, "KeyboardInput"},
	{InputType::MouseInput, "MouseInput"},
	{InputType::JoystickInput, "JoystickInput"}
		})
}
namespace Settings {
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ActorSettings, collision, type, position, collider_size, velocity, tick, drawable_collision_box);
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(AnimationSettings, rect_size, switch_time, frames_count, direction_to_row);
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(EngineSettings, window_settings_path, music_settings_path, world_settings_path);
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(MusicSettings, master_vol, music_vol, effect_vol);
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(TextureSettings, texture_path, smooth, repeatable);
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(WindowSettings, video_mode, fps, display_style, window_name, vsync);
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(WorldSettings, buffer_size, gc_frequent_level, cycle_to_move);
}