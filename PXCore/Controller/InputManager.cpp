#include "InputManager.h"
namespace Core::Controller {
	void InputManager::PressedBtn(const sf::Event& action)
	{
		if (!(action.type == sf::Event::EventType::KeyPressed
			or action.type == sf::Event::EventType::MouseButtonPressed))
			return;
		if (auto key = ConvertSfEventToKey(action); key)
			_clicked_btn.insert(*key);
	}
	void InputManager::ReleasedBtn(const sf::Event& action) {
		if (!(action.type == sf::Event::EventType::KeyReleased
			or action.type == sf::Event::EventType::MouseButtonReleased))
			return;
		if (auto key = ConvertSfEventToKey(action); key) {
			if (auto key_from_set = ClickedBtnContainsKey(*key); key_from_set) {
				_clicked_btn.erase(*key_from_set);
			}
		}
	}

	std::optional<std::reference_wrapper<const Key>> InputManager::ClickedBtnContainsKey(const Key& key) const
	{
		for (const auto& current_key : _clicked_btn) {
			if (current_key.input_type == key.input_type
				and key.input_type == InputType::KeyboardInput) {
				if (current_key.keyboard_button == key.keyboard_button)
					return std::optional(std::cref(current_key));
			}
			else if (current_key.input_type == key.input_type
				and key.input_type == InputType::MouseInput) {
				if (current_key.mouse_button == key.mouse_button)
					return std::optional(std::cref(current_key));
			}
		}
		return {};
	}

	void InputManager::ServiceEvent(const sf::Event& action) {
		if (action.type == sf::Event::EventType::KeyPressed
			or action.type == sf::Event::EventType::MouseButtonPressed)
			PressedBtn(action);
		else if (action.type == sf::Event::EventType::KeyReleased
			or action.type == sf::Event::EventType::MouseButtonReleased)
			ReleasedBtn(action);
	}

	const std::set<Core::Controller::Key>& InputManager::GetClickedBtn() const {
		return _clicked_btn;
	}

	std::optional<Core::Controller::Key> InputManager::ConvertSfEventToKey(const sf::Event& action)
	{
		if (!(action.type == sf::Event::EventType::KeyPressed
			or action.type == sf::Event::EventType::KeyReleased
			or action.type == sf::Event::EventType::MouseButtonPressed
			or action.type == sf::Event::EventType::MouseButtonReleased))
			return {};
		Key result;
		if (action.type == sf::Event::EventType::KeyPressed
			or action.type == sf::Event::EventType::KeyReleased) {
			result.input_type = Core::Controller::InputType::KeyboardInput;
			result.keyboard_button = action.key.code;
		}
		else {
			result.input_type = Core::Controller::InputType::MouseInput;
			result.mouse_button = action.mouseButton.button;
		}
		result.event_type = action.type;
		return result;
	}
}