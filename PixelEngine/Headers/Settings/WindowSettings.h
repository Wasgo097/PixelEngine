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
			std::stringstream stream;
			stream<< "VideoMode (whb): "<<_videomode.width<< " " <<_videomode.height <<" "<<_videomode.bitsPerPixel<< " Fps: " << _fps<< " Style: "<< _style<< " Window Name: " << _winname << " VSync: " <<_vsync;
			return stream.str();
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
		sf::VideoMode _videomode = sf::VideoMode(1920, 1080);
		int _fps = 30;
		unsigned int _style = sf::Style::Fullscreen;
		std::string _winname="Window";
		bool _vsync = false;
	};
}
