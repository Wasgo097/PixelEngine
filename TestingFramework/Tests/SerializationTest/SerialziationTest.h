#pragma once
#include "BaseTest.h"
#include <string>
#include <Settings/ActorSettings.h>
#include <Settings/AnimationSettings.h>
#include <Settings/EngineSettings.h>
#include <Settings/MusicSettings.h>
#include <Settings/TextureSettings.h>
#include <Settings/WindowSettings.h>
#include <Settings/WorldSettings.h>
using namespace Settings;
namespace Test{
	class SerialziationTest :public BaseTest{
	public:
		SerialziationTest(std::string rootpath);
	public:
		// Inherited via BaseTest
		virtual void PrepareTest();
		virtual bool RunTest();
	protected:
		std::string _rootpath;
	private:
		ActorSettings _actor_settings;
		AnimationSettings _animation_settings;
		EngineSettings _engine_settings;
		MusicSettings _music_settings;
		TextureSettings _texture_settings;
		WindowSettings _window_settings;
		WorldSettings _world_settings;
	};
}