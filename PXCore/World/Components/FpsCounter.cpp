#include "FpsCounter.h"
namespace Core::World::Component {
	FpsCounter::FpsCounter(BaseWorldGUI* parent, tgui::Gui* gui) :WorldBaseGUIComponent(parent, gui) {
	}
	void FpsCounter::InitComponent() {
		_fps_label = tgui::Label::create(); 
		_fps_label->setText("");
		_fps_label->setPosition({ "90%", "5%" });
		_gui->add(_fps_label);
	}
	void FpsCounter::Tick(float delta_time) {
		std::string text = "FPS: ";
		text += std::to_string(1.0f / delta_time);
		_fps_label->setText(text);
	}
}