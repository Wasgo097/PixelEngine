#include "Tests/EngineSettup/EngineSetupTest.h"
#include "Tests/ActorAnimation/ActorAnimationTest.h"
#include "Tests/Forest/ForestTest.h"
#include "Tests/GUISettup/GUISettupTest.h"
#include <iostream>
using namespace Test;
int main(){
	/*EngineSetupTest test1;
	std::cout << "Engine setup test result: \n" << test1.RunTest() << std::endl;*/
	/*ActorAnimationTest test2;
	std::cout << "Animation test result: \n" << test2.RunTest() << std::endl;*/
	ForestTest test3;
	std::cout << "Forest test result: \n" << test3.RunTest() << std::endl;
	/*GUISettupTest test4;
	std::cout << "GUI test result: \n" << test4.RunTest() << std::endl;*/
	return 0;
}