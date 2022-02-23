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
class SettingsFactory{
public:
	static Settings::ActorSettings CreateActorSettings(std::string path);
	static Settings::AnimationSettings CreateAnimationSettings(std::string path);
	static Settings::EngineSettings CreateEngineSettings(std::string path);
	static Settings::MusicSettings CreateMusicSettings(std::string path);
	static Settings::TextureSettings CreateTextureSettings(std::string path);
	static Settings::WindowSettings CreateWindowSettings(std::string path);
	static Settings::WorldSettings CreateWorldSettings(std::string path);
};