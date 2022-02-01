#pragma once
#include"SettingsBase.h"
#include "Utility/ISerializable.h"
#include <optional>
using nlohmann::json;
namespace Settings{
	class TextureSettings:public SettingsBase, Utility::IJsonSerializable{
	public:
		TextureSettings(std::optional<std::string> texture, bool smooth, bool repeatable);
		TextureSettings() = default;
	public:
		// Inherited via SettingsBase
		virtual std::string ToStdString()const override;
		// Inherited via IJsonSerializable
		virtual json JSerialize() const override;
		virtual bool JDeserialize(json json) override;
	public:
		const std::optional<std::string>& TexturePath()const;
		bool  Smooth()const;
		bool  Repeatable()const;
	protected:
		std::optional<std::string> _texturepath;
		bool _smooth = false;
		bool _repeatable = false;
	};
}