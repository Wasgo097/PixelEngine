#pragma once
#include "SettingsBase.h"
#include "Utility/BasicSFMLTypesToJson.h"
#include <SFML/Window.hpp>
namespace Settings{
	class WindowSettings :public SettingsBase{
	public:
		WindowSettings(sf::VideoMode mode, int fps, unsigned int style, std::string winname, bool vsync) :_videomode(mode), _fps(fps), _style(style), _winname(winname), _vsync(vsync) {}
		WindowSettings() = default;
	public:
		// Inherited via SettingsBase
		virtual std::string ToStdString()const override;
	public:
		sf::VideoMode _videomode;
		int _fps = 30;
		unsigned int _style = sf::Style::Fullscreen;
		std::string _winname="Window";
		bool _vsync = false;
		bool operator ==(const WindowSettings& obj)const {
			return (_videomode == obj._videomode) &&
				(_fps == obj._fps) &&
				(_style == obj._style) &&
				(_winname == obj._winname) &&
				(_vsync == obj._vsync);
		}
	};
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(WindowSettings, _videomode, _fps, _style, _winname, _vsync)
}
