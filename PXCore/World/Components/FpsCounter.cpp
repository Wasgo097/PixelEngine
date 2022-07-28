#include "FpsCounter.h"
namespace Core::World::Component {
	FpsCounter::FpsCounter(WorldBaseGUI* parent, tgui::Gui* gui, std::optional<tgui::Theme> theme) :WorldBaseGUIComponent(parent, gui,theme) {
	}
	void FpsCounter::InitComponent() {
		_fps_label = tgui::Label::create();
		_fps_label->setText("");
		_fps_label->setPosition({ "90%", "5%" });
		if (_theme)
			_fps_label->setRenderer(_theme->getRenderer("Label"));
		SetTickFlag(true);
	}
	void FpsCounter::Tick(float delta_time) {
		std::string text = "FPS: ";
		text += std::to_string(1.0f / delta_time);
		_fps_label->setText(text);
	}
	void FpsCounter::Draw() {
		_gui->add(_fps_label);
	}
}