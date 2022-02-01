#pragma once
#include "SettingsBase.h"
#include "Utility/ISerializable.h"
#include <SFML/Window.hpp>
using nlohmann::json;
namespace Settings{
	class WindowSettings :public SettingsBase, Utility::IJsonSerializable{
	public:
		WindowSettings(const sf::VideoMode& mode, int fps, unsigned int style, const std::string & winname, bool vsync);
		WindowSettings() = default;
	public:
		// Inherited via SettingsBase
		virtual std::string ToStdString()const override;

		// Inherited via IJsonSerializable
		virtual json JSerialize() const override;
		virtual bool JDeserialize(json json) override;
	public:
		const sf::VideoMode& GetVideoMode()const;
		const int& GetFps()const;
		unsigned int GetStyle()const;
		const std::string& GetWinName()const;
		bool  GetVSync()const;
	protected:
		sf::VideoMode _videomode = sf::VideoMode(1920, 1080);
		int _fps = 30;
		unsigned int _style = sf::Style::Fullscreen;
		std::string _winname="Window";
		bool _vsync = false;
	};
}
