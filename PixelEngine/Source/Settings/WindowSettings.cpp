#include "Settings/WindowSettings.h"
namespace Settings{
	WindowSettings::WindowSettings(sf::VideoMode && mode, int fps, unsigned int style, std::string && winname):_videomode(std::move(mode)),_fps(fps),_style(style),_winname(std::move(_winname)){}
	const sf::VideoMode & WindowSettings::GetVideoMode() const{
		return _videomode;
	}
	const int & WindowSettings::GetFps() const{
		return _fps;
	}
	const unsigned int & WindowSettings::GetStyle() const{
		return _style;
	}
	const std::string & WindowSettings::GetWinName() const{
		return _winname;
	}
}