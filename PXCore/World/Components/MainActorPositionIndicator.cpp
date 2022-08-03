#include "MainActorPositionIndicator.h"
namespace Core::World::Component {
	MainActorPositionIndicator::MainActorPositionIndicator(WorldBaseGUI* parent, tgui::Gui* gui, std::optional<tgui::Theme> theme, std::shared_ptr<Core::Object::ControlledActor> tracked_actor) :
		WorldBaseGUIComponent(parent, gui, theme), _actor{ tracked_actor } {
	}
	void MainActorPositionIndicator::InitComponent() {
		_position_label = tgui::Label::create();
		_position_label->setText("");
		_position_label->setPosition({ "90%", "15%" });
		if (_theme)
			_position_label->setRenderer(_theme->getRenderer("Label"));
		SetTickFlag(true);
		_initialized = true;
	}
	void MainActorPositionIndicator::Tick(float delta_time) {
		if (!_initialized)
			throw std::runtime_error("Tick uninitialized WorldComponent");
		else if (!_actor.expired()) {
			if (auto position = _actor.lock()->GetPosition(); position) {
				std::stringstream s_stream;
				s_stream << "X: " << position->x << "\nY: " << position->y;
				_position_label->setText(s_stream.str());
			}
		}
	}
	void MainActorPositionIndicator::Draw() {
		if (!_initialized)
			throw std::runtime_error("Draw uninitialized WorldComponent");
		else if (!_actor.expired())
			_gui->add(_position_label);
	}
}