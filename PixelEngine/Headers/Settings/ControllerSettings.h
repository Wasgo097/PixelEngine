#pragma once
#include "SettingsBase.h"
#include "Objects/ControlledActor.h"
#include "Controller/ControllerStructs.h"
namespace Settings{
	class ControllerSettings :public SettingsBase{
	public:
		//ControllerSettings(std::map<Controller::Key, std::function<void(Core::ControlledActor*)>> actions):_actions(actions){}
		ControllerSettings() = default;
		// Inherited via SettingsBase
		virtual std::string ToStdString() const override{
			return "";
		}
		/*std::map<Controller::Key, std::function<void(Core::ControlledActor*)>> & GetActions(){
			return _actions;
		}*/
	protected:
		//std::map<Controller::Key, std::function<void(Core::ControlledActor*)>> _actions;
	};
}