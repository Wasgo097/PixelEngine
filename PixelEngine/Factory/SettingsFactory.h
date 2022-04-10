#pragma once
#include "Settings/ActorSettings.h"
#include "Settings/AnimationSettings.h"
#include "Settings/EngineSettings.h"
#include "Settings/MusicSettings.h"
#include "Settings/TextureSettings.h"
#include "Settings/WindowSettings.h"
#include "Settings/WorldSettings.h"
#include <fstream>
#include <string>
#include <iostream>
#define CREATE_SETTINGS(settingsclass,path)Factory::SettingsFactory<settingsclass>::CreateSettings(path);
#define CREATE_SETTINGS_FILE(settingsclass,path,settingsobject)Factory::SettingsFactory<settingsclass>::CreateSettingsJsonFile(path,settingsobject);
namespace Factory {
	template<class T>
	class SettingsFactory{
	public:
		static T CreateSettings(std::string path) {
			T result;
			std::ifstream stream(path, std::fstream::in);
			try {
				if (stream.is_open()) {
					json jobj;
					stream >> jobj;
					result = jobj.get<T>();
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
		static void CreateSettingsJsonFile(std::string path, const T& settings = T()) {
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