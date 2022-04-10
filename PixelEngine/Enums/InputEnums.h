#pragma once
#include "Utility/json.hpp"
namespace Controller {
	enum class InputType {
		KeyboardInput,
		MouseInput,
		JoystickInput
	};
	NLOHMANN_JSON_SERIALIZE_ENUM(InputType, {
	{InputType::KeyboardInput, "KeyboardInput"},
	{InputType::MouseInput, "MouseInput"},
	{InputType::JoystickInput, "JoystickInput"}
		})
}