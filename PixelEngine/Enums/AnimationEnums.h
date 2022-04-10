#pragma once
#include"Utility/json.hpp"
namespace AnimationEnums {
	enum class Direction {
		None,
		Left,
		Up,
		Right,
		Down,
		LeftIdle,
		UpIdle,
		RightIdle,
		DownIdle
	};
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