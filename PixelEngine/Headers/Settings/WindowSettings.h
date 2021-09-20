#pragma once
#include "SettingsBase.h"
#include "CommonHeaders.h"
namespace Settings{
	class WindowSettings :public SettingsBase{
	public:
		WindowSettings(const sf::VideoMode& mode, int fps, unsigned int style, const std::string & winname,bool vsync):
			_videomode(mode), _fps(fps), _style(style), _winname(_winname),_vsync(vsync)
		{}
		WindowSettings() = default;
		// Inherited via SettingsBase
		virtual std::string ToStdString() override{
			return "VideoMode (wxhxb): "+std::to_string(_videomode.width)+"x"+ std::to_string(_videomode.height) + "x" + std::to_string(_videomode.bitsPerPixel) + " Fps: "+std::to_string(_fps)+" Style: "+std::to_string(_style)
				+" Window Name: "+_winname+" VSync: "+std::to_string(_vsync);
		}
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
