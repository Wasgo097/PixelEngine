#include "ControllerBase.h"
#include <iostream>
namespace Core::Controller {
	void ControllerBase::ServiceInput(const Core::Controller::Key& key) {
		if (auto key_from_map=ActionsContainsKey(key);key_from_map)
			_actions[*key_from_map](_main_character);
	}
	std::shared_ptr<Object::ControlledActor> ControllerBase::GetMainCharacter() {
		return _main_character;
	}
	std::optional<std::reference_wrapper<const Key>> Controller::ControllerBase::ActionsContainsKey(const Key& key) const
	{
		for (const auto& [current_key, _] : _actions) {
			if (current_key.input_type == key.input_type
				and key.input_type == InputType::KeyboardInput) {
				if (current_key.event_type == key.event_type
					and current_key.keyboard_button == key.keyboard_button)
					return std::optional(std::cref(current_key));
			}
			else if (current_key.input_type == key.input_type
				and key.input_type == InputType::MouseInput) {
				if (current_key.event_type == key.event_type
					and current_key.mouse_button == key.mouse_button)
					return std::optional(std::cref(current_key));
			}
		}
		return {};
	}
}