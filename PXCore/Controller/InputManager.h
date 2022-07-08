#pragma once
#include <unordered_map>
#include <optional>
#include <vector>
#include "PXUtilities/ControllerStructs.h"
namespace Core::Controller {
	class InputManager
	{
	public:
		void PressedBtn(const sf::Event& action);
		void ReleasedBtn(const sf::Event& action);
		std::vector<Core::Controller::Key> GetPressedKeys()const;
		static std::optional<Core::Controller::Key> ConvertSfEventToKey(const sf::Event& action);
	private:
		std::unordered_map<Core::Controller::Key, bool> _clicked_btn;
	};
}