#include "InputManager.h"
namespace Core::Controller {
	void InputManager::PressedBtn(const sf::Event& action)
	{
		if (action.type == sf::Event::EventType::KeyPressed
			or action.type == sf::Event::EventType::MouseButtonPressed)
			if (auto key = ConvertSfEventToKey(action); key)
				_clicked_btn.insert(*key);
	}
	void InputManager::ReleasedBtn(const sf::Event& action) {
		if (action.type == sf::Event::EventType::KeyReleased
			or action.type == sf::Event::EventType::MouseButtonReleased)
			if (auto key = ConvertSfEventToKey(action); key and _clicked_btn.contains(*key))
				_clicked_btn.erase(*key);
	}

	const std::set<Core::Controller::Key>& InputManager::GetClickedBtn() const{
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