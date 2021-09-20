#pragma once
#include "CommonHeaders.h"
namespace Settings{
	class WindowSettings{
	public:
		WindowSettings(const sf::VideoMode& mode, int fps, unsigned int style, const std::string & winname,bool vsync):
			_videomode(mode), _fps(fps), _style(style), _winname(_winname),_vsync(vsync)
		{}
		WindowSettings() = default;
		const sf::VideoMode& GetVideoMode()const{
			return _videomode;
		}
		const int& GetFps()const{
			return _fps;
		}
		const unsigned int& GetStyle()const{
			return _style;
		}
		const std::string& GetWinName()const{
			return _winname;
		}
		const bool & GetVSync()const{
			return _vsync;
		}
	protected:
		sf::VideoMode _videomode;
		int _fps;
		unsigned int _style;
		std::string _winname;
		bool _vsync;
	};
}
