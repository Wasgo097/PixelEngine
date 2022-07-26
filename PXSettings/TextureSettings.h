#pragma once
#include <string>
namespace Settings {
	struct TextureSettings{
		TextureSettings(const std::string& texture, bool smooth, bool repeatable) :texture_path{ texture }, smooth{ smooth }, repeatable{ repeatable } {}
		TextureSettings() = default;

		bool operator==(const TextureSettings& obj)const {
			return texture_path == obj.texture_path && smooth == obj.smooth && repeatable == obj.repeatable;
		}

		std::string texture_path;
		bool smooth = false;
		bool repeatable = false;
		float scale = 1.0f;
	};
}