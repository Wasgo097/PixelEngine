#include "Tests/EngineSettup/EngineSetupTest.h"
#include "Tests/ActorAnimation/ActorAnimationTest.h"
#include "Tests/Forest/ForestTest.h"
#include "Tests/GUISettup/MultipleWidgetsTest.h"
#include "Tests/GUISettup/LoginExample.h"
#include "Tests/MainMenu/MainMenuTest.h"
#include <iostream>
using namespace Test;
int main(int argc, char** argv){
	/*EngineSetupTest test1;
	std::cout << "Engine setup test result: \n" << test1.RunTest() << std::endl;*/
	/*ActorAnimationTest test2;
	std::cout << "Animation test result: \n" << test2.RunTest() << std::endl;*/
	/*ForestTest test3;
	std::cout << "Forest test result: \n" << test3.RunTest() << std::endl;*/
	/*LoginExample test4;
	std::cout << "LoginExample result: \n" << test4.RunTest() << std::endl;*/
	/*MultipleWidgetsTest test5;
	std::cout << "MultipleWidgetsTest result: \n" << test5.RunTest() << std::endl;*/
	MainMenuTest test6;
	std::cout << "MainMenuTest result: \n" << test6.RunTest() << std::endl;
	return 0;
}