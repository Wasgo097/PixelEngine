#pragma once
#include "SettingsBase.h"
#include "Controller/ControllerStructs.h"
namespace Settings{
	class ControlSettings :public SettingsBase{
	public:
		ControlSettings();
		ControlSettings() = default;
		// Inherited via SettingsBase
		virtual std::string ToStdString() const override;
	protected:
		std::map<Controller::Key, std::function<void()>> _actions;
	};
}