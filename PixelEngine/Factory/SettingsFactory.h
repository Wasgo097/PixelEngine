#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <concepts>
#include "Utility/Serialization.h"
#define CREATE_SETTINGS(SettingsClass,Path)Factory::SettingsFactory::CreateSettings<SettingsClass>(Path);
#define CREATE_SETTINGS_FILE(SettingsObj,Path)Factory::SettingsFactory::CreateSettingsJsonFile(Path,SettingsObj);
namespace Factory {
	class SettingsFactory {
	public:
		template<class T>
			requires std::derived_from<T, Settings::SettingsBase>
		static T CreateSettings(const std::string& path) {
			T result;
			std::ifstream stream(path, std::fstream::in);
			try {
				if (stream.is_open()) {
					json jobj;
					stream >> jobj;
					result = jobj;
				}
				else {
					std::cout << "Error in SettingsFactory<" << typeid(T).name() << ">::CreateSettings. Cant open path: " << path << std::endl;
				}
			}
			catch (...) {
				std::cout << "Fatal error in SettingsFactory<" << typeid(T).name() << ">::CreateSettings. Path: " << path << std::endl;
			}
			stream.close();
			return result;
		}
		template<class T>
			requires std::derived_from<T, Settings::SettingsBase>
		static void CreateSettingsJsonFile(const std::string& path, const T& settings = T()) {
			std::ofstream stream(path, std::ofstream::out);
			if (stream.is_open()) {
				json jobj = settings;
				stream << jobj.dump(4);
				stream.close();
			}
			else {
				std::cout << "Error in SettingsFactory<" << typeid(T).name() << ">::CreateSettingsJsonFile. Path " << path << std::endl;
			}
		}
	};
}