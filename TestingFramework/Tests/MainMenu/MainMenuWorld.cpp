#include "MainMenuWorld.h"
#include "MainMenuEngine.h"
#include "Tests/Forest/WorldForForestTest.h"
#include "PXFactory/SettingsFactory.h"
namespace Test {
	MainMenuWorld::MainMenuWorld(Settings::WindowSettingsDTO& window_settings, const Settings::WorldSettings& world_settings, Core::Engine* parent) :
		WorldBase(world_settings, parent), _gui(*parent->GetWindow()), _window_settings(window_settings) {
	}
	void MainMenuWorld::Draw(sf::RenderWindow& window) {
		WorldBase::Draw(window);
		window.clear(sf::Color::Green);
		_gui.draw();
	}
	void MainMenuWorld::ServiceInput(const sf::Event& action) {
		_gui.handleEvent(action);
	}
	void MainMenuWorld::InitWorld() {
		DefaultGuiSettup();
		_initialized = true;
	}
	void updateTextSize(tgui::GuiBase& gui) {
		const float windowHeight = gui.getView().getRect().height;
		gui.setTextSize(static_cast<unsigned int>(0.03f * windowHeight));
	}
	void MainMenuWorld::CommonGuiSettup() {
		_gui.removeAllWidgets();
		updateTextSize(_gui);
		auto picture = tgui::Picture::create("Resource\\GUI\\fantasy_background.png");
		picture->setSize({ "100%", "100%" });
		_gui.add(picture);
	}
	void MainMenuWorld::DefaultGuiSettup() {
		CommonGuiSettup();
		auto new_game_btn = tgui::Button::create("New Game");
		new_game_btn->setSize({ "20%", "15%" });
		new_game_btn->setPosition({ "40%", "40%" });
		_gui.add(new_game_btn);
		new_game_btn->onPress(&MainMenuWorld::NewGameClick, this);
		auto settings_btn = tgui::Button::create("Settings");
		settings_btn->setSize({ "20%", "15%" });
		settings_btn->setPosition({ "40%", "60%" });
		_gui.add(settings_btn);
		settings_btn->onPress(&MainMenuWorld::SettingsClick, this);
		auto exit_btn = tgui::Button::create("Exit Game");
		exit_btn->setSize({ "20%", "15%" });
		exit_btn->setPosition({ "40%", "80%" });
		_gui.add(exit_btn);
		exit_btn->onPress(&MainMenuWorld::ExitClick, this);
	}
	void MainMenuWorld::NewGameClick() {
		_parent->PushWorldToQueue(std::make_unique<WorldForForestTest>(_world_settings, _parent));
		std::cout << "New Game clicked\n";
		_quit = true;
	}
	void MainMenuWorld::SettingsClick() {
		CommonGuiSettup();
		_working_window_settings = std::make_unique<Settings::WindowSettingsDTO>(_window_settings);
		auto return_btn = tgui::Button::create("<-");
		return_btn->setSize({ "5%", "5%" });
		return_btn->setPosition({ "2%", "5%" });
		_gui.add(return_btn);
		return_btn->onPress(&MainMenuWorld::DefaultGuiSettup, this); 
		auto apply_btn = tgui::Button::create("Apply");
		apply_btn->setSize({ "5%", "5%" });
		apply_btn->setPosition({ "2%", "10%" });
		_gui.add(apply_btn);
		apply_btn->onPress(&MainMenuWorld::ApplySettings, this);
		//resolution
		auto label = tgui::Label::create();
		label->setText("Resolutions:");
		label->setPosition({ "5%", "30%" });
		_gui.add(label);
		_resolutions_tabs = tgui::Tabs::create();
		_resolutions_tabs->setTabHeight(30);
		_resolutions_tabs->setPosition({ "15%", "30%" });
		_resolutions_tabs->add("1280*720");
		_resolutions_tabs->add("1680*1050");
		_resolutions_tabs->add("1920*1080");
		_gui.add(_resolutions_tabs);
		if (_window_settings.video_mode.height == 720 and _window_settings.video_mode.width == 1280)
			_resolutions_tabs->select(0);
		else if (_window_settings.video_mode.height == 1050 and _window_settings.video_mode.width == 1680)
			_resolutions_tabs->select(1);
		else if (_window_settings.video_mode.height == 1080 and _window_settings.video_mode.width == 1920)
			_resolutions_tabs->select(2);
		else
			_resolutions_tabs->select(0);
		_resolutions_tabs->onTabSelect(&MainMenuWorld::RewriteSettings, this);
		//fps
		label = tgui::Label::create();
		label->setText("Fps:");
		label->setPosition({ "5%", "45%" });
		_gui.add(label);
		_fps_slider = tgui::Slider::create();
		_fps_slider->setPosition({ "15%", "45%" });
		_fps_slider->setMinimum(0.0f);
		_fps_slider->setMaximum(120.0f);
		_fps_slider->setValue(static_cast<float>(_window_settings.fps));
		_fps_slider->setStep(10.0f);
		_gui.add(_fps_slider);
		_fps_slider->onValueChange(&MainMenuWorld::RewriteSettings, this);
		//window mode
		label = tgui::Label::create();
		label->setText("Window mode:");
		label->setPosition({ "5%", "65%" });
		_gui.add(label);
		_fullscreen_radio = tgui::RadioButton::create();
		_fullscreen_radio->setPosition({ "15%", "62%" });
		_fullscreen_radio->setText("Fullscreen!");
		_gui.add(_fullscreen_radio);
		_window_radio = tgui::RadioButton::create();
		_window_radio->setPosition({ "15%", "72%" });
		_window_radio->setText("Window");
		_gui.add(_window_radio);
		if (_window_settings.display_style == 8) {
			_fullscreen_radio->setChecked(true);
			_window_radio->setChecked(false);
		}
		else {
			_window_radio->setChecked(true);
			_fullscreen_radio->setChecked(false);
		}
		_window_radio->onCheck(&MainMenuWorld::RewriteSettings, this);
		_fullscreen_radio->onCheck(&MainMenuWorld::RewriteSettings, this);
	}
	void MainMenuWorld::ExitClick() {
		std::cout << "Exit clicked\n";
		_quit = true;
	}
	void MainMenuWorld::ReturnClick() {
		DefaultGuiSettup();
	}
	void MainMenuWorld::RewriteSettings() {
		_working_window_settings->fps = static_cast<int>(_fps_slider->getValue());
		if (_fullscreen_radio->isChecked())
			_working_window_settings->display_style = 8;
		else if (_window_radio->isChecked())
			_working_window_settings->display_style = 7;
		if (_resolutions_tabs->getSelectedIndex() == 0) {
			_working_window_settings->video_mode.width = 1280;
			_working_window_settings->video_mode.height = 720;
		}
		else if (_resolutions_tabs->getSelectedIndex() == 1) {
			_working_window_settings->video_mode.width = 1680;
			_working_window_settings->video_mode.height = 1050;
		}
		else if (_resolutions_tabs->getSelectedIndex() == 2) {
			_working_window_settings->video_mode.width = 1920;
			_working_window_settings->video_mode.height = 1080;
		}
	}
	void MainMenuWorld::ApplySettings(){
		if (auto engine = dynamic_cast<MainMenuEngine*>(_parent); engine != nullptr) {
			std::cout << "Apply new settings\n";
			engine->ApplyWindowSettings(*_working_window_settings);
			//fix for wrong coord convert
			_gui.setTarget(*_parent->GetWindow());
			SettingsClick();
		}
	}
}