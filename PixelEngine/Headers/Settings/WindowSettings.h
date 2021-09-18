#pragma once
#include "CommonHeaders.h"
namespace Settings{
	class WindowSettings{
	public:
		WindowSettings(sf::VideoMode&& mode, int fps, unsigned int style, std::string && winname)
			:_videomode(std::move(mode)), _fps(fps), _style(style), _winname(std::move(_winname)){}
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
	protected:
		sf::VideoMode _videomode;
		int _fps;
		unsigned int _style;
		std::string _winname;
	};
}
