#pragma once
#include "SettingsBase.h"
#include "Utility/ISerializable.h"
using nlohmann::json;
namespace Settings{
	class EngineSettings:public SettingsBase, Utility::IJsonSerializable{
	public:
		EngineSettings(std::string rootpath, std::string winsettings, std::string mussettings, std::string worldsettings);
		EngineSettings() = default;
	public:
		// Inherited via SettingsBase
		virtual std::string ToStdString()const override;
		// Inherited via IJsonSerializable
		virtual json JSerialize() const override;
		virtual bool JDeserialize(json json) override;
	public:
		const std::string & WindowSettings()const;
		const std::string & MusicSettings()const;
		const std::string & WorldSettings()const;
	protected:
		std::string _rootpath="";
		std::string _windowsettings="";
		std::string _musicsettings = "";
		std::string _worldsettings = "";

	};
}