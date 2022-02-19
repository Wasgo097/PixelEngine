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
		ActorSettings _actorsettings;
		AnimationSettings _animationsettings;
		EngineSettings _enginesettings;
		MusicSettings _musicsettings;
		TextureSettings _texturesettings;
		WindowSettings _windowsettings;
		WorldSettings _worldsettings;
	};
}