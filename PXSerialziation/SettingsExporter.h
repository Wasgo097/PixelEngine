#pragma once
#include <string>
#include <fstream>
#include "json.hpp"
using nlohmann::json;
namespace Serialization {
	template<typename T>
	void ExportSettingsToFile(const std::string& path, T settings_obj) {
		std::ofstream stream(path);
		json jsettings = settings_obj;
		stream << jsettings.dump(4);
		stream.close();
	}
}