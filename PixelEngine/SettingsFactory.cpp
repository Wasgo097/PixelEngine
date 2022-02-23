#include "SettingsFactory.h"
#include <iostream>
using namespace Settings;
Settings::ActorSettings SettingsFactory::CreateActorSettings(std::string path){
	ActorSettings result;
	try {
		std::ifstream stream(path, std::fstream::in);
		if (stream.is_open()) {
			json jobj;
			jobj << stream;
			result = jobj.get<ActorSettings>();
		}
		else {
			std::cout << "Error with SettingsFactory::CreateActorSettings. Path " << path << std::endl;
		}
	}
	catch (...) {
		std::cout << "Fatal error in SettingsFactory::CreateActorSettings. Path " << path << std::endl;
	}
	return result;
}

Settings::AnimationSettings SettingsFactory::CreateAnimationSettings(std::string path){
	AnimationSettings result;
	try {
		std::ifstream stream(path, std::fstream::in);
		if (stream.is_open()) {
			json jobj;
			jobj << stream;
			result = jobj.get<AnimationSettings>();
		}
		else {
			std::cout << "Error with SettingsFactory::CreateAnimationSettings. Path " << path << std::endl;
		}
	}
	catch (...) {
		std::cout << "Fatal error in SettingsFactory::CreateAnimationSettings. Path " << path << std::endl;
	}
	return result;
}

Settings::EngineSettings SettingsFactory::CreateEngineSettings(std::string path){
	EngineSettings result;
	try {
		std::ifstream stream(path, std::fstream::in);
		if (stream.is_open()) {
			json jobj;
			jobj << stream;
			result = jobj.get<EngineSettings>();
		}
		else {
			std::cout << "Error with SettingsFactory::CreateEngineSettings. Path " << path << std::endl;
		}
	}
	catch (...) {
		std::cout << "Fatal error in SettingsFactory::CreateEngineSettings. Path " << path << std::endl;
	}
	return result;
}

Settings::MusicSettings SettingsFactory::CreateMusicSettings(std::string path){
	MusicSettings result;
	try {
		std::ifstream stream(path, std::fstream::in);
		if (stream.is_open()) {
			json jobj;
			jobj << stream;
			result = jobj.get<MusicSettings>();
		}
		else {
			std::cout << "Error with SettingsFactory::CreateMusicSettings. Path " << path << std::endl;
		}
	}
	catch (...) {
		std::cout << "Fatal error in SettingsFactory::CreateMusicSettings. Path " << path << std::endl;
	}
	return result;
}

Settings::TextureSettings SettingsFactory::CreateTextureSettings(std::string path){
	TextureSettings result;
	try {
		std::ifstream stream(path, std::fstream::in);
		if (stream.is_open()) {
			json jobj;
			jobj << stream;
			result = jobj.get<TextureSettings>();
		}
		else {
			std::cout << "Error with SettingsFactory::CreateTextureSettings. Path " << path << std::endl;
		}
	}
	catch (...) {
		std::cout << "Fatal error in SettingsFactory::CreateTextureSettings. Path " << path << std::endl;
	}
	return result;
}

Settings::WindowSettings SettingsFactory::CreateWindowSettings(std::string path){
	WindowSettings result;
	try {
		std::ifstream stream(path, std::fstream::in);
		if (stream.is_open()) {
			json jobj;
			jobj << stream;
			result = jobj.get<WindowSettings>();
		}
		else {
			std::cout << "Error with SettingsFactory::CreateWindowSettings. Path " << path << std::endl;
		}
	}
	catch (...) {
		std::cout << "Fatal error in SettingsFactory::CreateWindowSettings. Path " << path << std::endl;
	}
	return result;
}

Settings::WorldSettings SettingsFactory::CreateWorldSettings(std::string path){
	WorldSettings result;
	try {
		std::ifstream stream(path, std::fstream::in);
		if (stream.is_open()) {
			json jobj;
			jobj << stream;
			result = jobj.get<WorldSettings>();
		}
		else {
			std::cout << "Error with SettingsFactory::CreateWorldSettings. Path " << path << std::endl;
		}
	}
	catch (...) {
		std::cout << "Fatal error in SettingsFactory::CreateWorldSettings. Path " << path << std::endl;
	}
	return result;
}
