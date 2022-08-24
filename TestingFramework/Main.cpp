#include "Tests/EngineSettup/EngineSetupTest.h"
#include "Tests/ActorAnimation/ActorAnimationTest.h"
#include "Tests/Forest/ForestTest.h"
#include "Tests/GUISettup/MultipleWidgetsTest.h"
#include "Tests/GUISettup/LoginExample.h"
#include "Tests/MainMenu/MainMenuTest.h"
#include "Tests/ExampleParticle/ParticleTest.h"
#include "Tests/MyParticle/MyParticleTest.h"
#include "PXArgumentParser/ArgumentParser.h"
#include <iostream>
using namespace Test;
int main(int argc, const char* argv[]) {
	ArgumentParser parser(argc, argv);
	/*EngineSetupTest test1(parser);
	std::cout << "Engine setup test result: \n" << test1.RunTest() << std::endl;*/
	/*ActorAnimationTest test2(parser);
	std::cout << "Animation test result: \n" << test2.RunTest() << std::endl;*/
	/*ForestTest test3(parser);
	std::cout << "Forest test result: \n" << test3.RunTest() << std::endl;*/
	/*LoginExample test4(parser);
	std::cout << "LoginExample result: \n" << test4.RunTest() << std::endl;*/
	/*MultipleWidgetsTest test5(parser);
	std::cout << "MultipleWidgetsTest result: \n" << test5.RunTest() << std::endl;*/
	MainMenuTest test6(parser);
	std::cout << "MainMenuTest result: \n" << test6.RunTest() << std::endl;
	/*ParticleTest test7(parser);
	std::cout << "ParticleTest result: \n" << test7.RunTest() << std::endl;*/
	/*MyParticleTest test8(parser);
	std::cout << "MyParticleTest result: \n" << test8.RunTest() << std::endl;*/
	return 0;
}