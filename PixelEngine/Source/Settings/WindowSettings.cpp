#include "Settings/WindowSettings.h"
#include <sstream>
namespace Settings{
	WindowSettings::WindowSettings(const sf::VideoMode & mode, int fps, unsigned int style, const std::string & winname, bool vsync) :
		_videomode(mode), _fps(fps), _style(style), _winname(_winname), _vsync(vsync){}

	// Inherited via SettingsBase

	std::string WindowSettings::ToStdString() const{
		std::stringstream stream;
		stream << "VideoMode (whb): " << _videomode.width << " " << _videomode.height << " " << _videomode.bitsPerPixel << " Fps: " << _fps << " Style: " << _style << " Window Name: " << _winname << " VSync: " << _vsync;
		return stream.str();
	}
	const sf::VideoMode & WindowSettings::GetVideoMode() const{
		return _videomode;
	}
	const int & WindowSettings::GetFps() const{
		return _fps;
	}
	unsigned int  WindowSettings::GetStyle() const{
		return _style;
	}
	const std::string & WindowSettings::GetWinName() const{
		return _winname;
	}
	bool WindowSettings::GetVSync() const{
		return _vsync;
	}
	json WindowSettings::JSerialize() const{
		return json();
	}
	bool WindowSettings::JDeserialize(json json){
		return false;
	}
}