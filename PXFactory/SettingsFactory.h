#pragma once
#include <fstream>
#include <iostream>
#include "PXSerialziation/Serialization.h"
#define CREATE_SETTINGS(SettingsClass,Path)Factory::SettingsFactory::CreateSettings<SettingsClass>(Path);
#define CREATE_SETTINGS_FILE(SettingsObj,Path)Factory::SettingsFactory::CreateSettingsJsonFile(Path,SettingsObj);
namespace Factory {
	class SettingsFactory {
	public:
		template<class T>
		static T CreateSettings(const std::string& path) {
			T result;
			try {
				if (std::ifstream stream(path); stream.is_open()) {
					json jobj;
					stream >> jobj;
					result = jobj;
					stream.close();
				}
				else {
					std::cout << "Error in SettingsFactory<" << typeid(T).name() << ">::CreateSettings. Cant open path: " << path << std::endl;
				}
			}
			catch (...) {
				std::cout << "Fatal error in SettingsFactory<" << typeid(T).name() << ">::CreateSettings. Path: " << path << std::endl;
			}
			return result;
		}
		template<class T>
		static void CreateSettingsJsonFile(const std::string& path, const T& settings = T()) {
			if (std::ofstream stream(path); stream.is_open()) {
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