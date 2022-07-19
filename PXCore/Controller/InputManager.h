#pragma once
#include <set>
#include <optional>
#include "PXUtilities/ControllerStructs.h"
namespace Core::Controller {
	class InputManager {
	public:
		void ServiceEvent(const sf::Event& action);
		const std::set<Core::Controller::Key>& GetClickedBtn()const;
		const std::set< Core::Controller::Key>& GetReleasedBtn()const;
		void ClearReleasedBtn();
		static std::optional<Core::Controller::Key> ConvertSfEventToKey(const sf::Event& action);
	private:
		void PressedBtn(const sf::Event& action);
		void ReleasedBtn(const sf::Event& action);
		std::optional<std::reference_wrapper<const Key>> ClickedBtnContainsKey(const Key& key)const;
		std::set<Core::Controller::Key> _clicked_btn;
		std::set<Core::Controller::Key> _released_btn;
	};
}