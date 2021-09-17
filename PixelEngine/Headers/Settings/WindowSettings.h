#pragma once
#include "CommonHeaders.h"
namespace Settings{
	class WindowSettings{
	protected:
		sf::VideoMode _videomode;
		int _fps = 30;
		unsigned int _style = sf::Style::Default;
		std::string _winname;
	public:
		WindowSettings(sf::VideoMode&& mode, int fps, unsigned int style,std::string && winname);
		const sf::VideoMode& GetVideoMode()const;
		const int& GetFps()const;
		const unsigned int& GetStyle()const;
		const std::string& GetWinName()const;
	};
}
