#include "ControllerBase.h"
namespace Core::Controller {
	void ControllerBase::ServiceInput(const Core::Controller::Key& key) {
		if (auto key_from_map = ActionsContainsKey(key); key_from_map) {
			auto& ref_to_key = key_from_map->get();
			if (ref_to_key.repeatable)
				_actions[*key_from_map](_main_character);
			else if ((key.event_type == sf::Event::EventType::KeyPressed
				or key.event_type == sf::Event::EventType::MouseButtonPressed)
				and !ref_to_key.consumed) {
				_actions[*key_from_map](_main_character);
				ref_to_key.consumed = true;
			}
			else if ((key.event_type == sf::Event::EventType::KeyReleased
				or key.event_type == sf::Event::EventType::MouseButtonReleased)
				and ref_to_key.consumed)
				ref_to_key.consumed = false;
		}
	}
	std::shared_ptr<Object::ControlledActor> ControllerBase::GetMainCharacter() {
		return _main_character;
	}
	std::optional<std::reference_wrapper<const Key>> Controller::ControllerBase::ActionsContainsKey(const Key& key) const {
		for (const auto& [current_key, _] : _actions) {
			if (current_key.input_type == key.input_type
				and key.input_type == InputType::KeyboardInput
				and current_key.keyboard_button == key.keyboard_button) {
				return std::optional(std::cref(current_key));
			}
			else if (current_key.input_type == key.input_type
				and key.input_type == InputType::MouseInput
				and current_key.mouse_button == key.mouse_button) {
				return std::optional(std::cref(current_key));
			}
		}
		return {};
	}
}