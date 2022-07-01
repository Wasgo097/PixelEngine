#pragma once
#include"SettingsBase.h"
namespace Settings {
	struct TextureSettings :public SettingsBase {
		TextureSettings(std::string texture, bool smooth, bool repeatable) :texture_path{ texture }, smooth{ smooth }, repeatable{ repeatable } {}
		TextureSettings() = default;
		virtual std::string ToStdString()const override;
		std::string texture_path;
		bool smooth = false;
		bool repeatable = false;

		auto operator <=>(const TextureSettings&)const = default;
	};
}