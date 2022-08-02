#include "ActorsCounter.h"
namespace Core::World::Component {
	ActorsCounter::ActorsCounter(Core::World::WorldBaseGUI* parent, tgui::Gui* gui, std::optional<tgui::Theme> theme) :WorldBaseGUIComponent(parent, gui, theme) {
	}
	void ActorsCounter::SetCountOfActors(size_t new_count) {
		_counter->setText(std::to_string(new_count));
	}
	void ActorsCounter::InitComponent() {
		_counter = tgui::Label::create();
		_counter->setText("");
		_counter->setPosition({ "90%", "10%" });
		if (_theme)
			_counter->setRenderer(_theme->getRenderer("Label"));
		SetTickFlag(false);
	}
	void ActorsCounter::Draw() {
		_gui->add(_counter);
	}
}