#include "ControllerBase.h"
#include "PXCore/Object/ControlledActor.h"
namespace Core::Controller {
	ControllerBase::ControllerBase(Core::World::WorldBase* world_parent, const Settings::WorldSettings& world_settings) :_world_parent{ world_parent },
		_deadzone{ world_settings.deadzone_x,world_settings.deadzone_y }{
	}
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
	bool Controller::ControllerBase::CheckMoveIsPossible(const sf::Vector2f& velocity) const {
		if (auto position = _main_character->GetPosition(); position) {
			const auto& nex_position = (*position) + velocity;
			return (nex_position.x > -std::abs(_deadzone.x) and nex_position.x < std::abs(_deadzone.x) and
				nex_position.y >-std::abs(_deadzone.y) and nex_position.y < std::abs(_deadzone.y));
		}
		return false;
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