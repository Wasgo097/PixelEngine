#include "Tests/EngineSettup/EngineSetupTest.h"
#include "Tests/ActorAnimation/ActorAnimationTest.h"
#include "Tests/Forest/ForestTest.h"
#include "Tests/GUISettup/MultipleWidgetsTest.h"
#include "Tests/GUISettup/LoginExample.h"
#include "Tests/MainMenu/MainMenuTest.h"
#include <iostream>
using namespace Test;
int main(){
	/*EngineSetupTest test1;
	std::cout << "Engine setup test result: \n" << test1.RunTest() << std::endl;*/
	/*ActorAnimationTest test2;
	std::cout << "Animation test result: \n" << test2.RunTest() << std::endl;*/
	ForestTest test3;
	std::cout << "Forest test result: \n" << test3.RunTest() << std::endl;
	/*LoginExample test4;
	std::cout << "LoginExample result: \n" << test4.RunTest() << std::endl;*/
	/*MultipleWidgetsTest test5;
	std::cout << "MultipleWidgetsTest result: \n" << test5.RunTest() << std::endl;*/
	/*MainMenuTest test6;
	std::cout << "MainMenuTest result: \n" << test6.RunTest() << std::endl;*/
	sf::Vector2f f{ 20,30 };
	sf::Vector2f f2{ 30,40 };
	//o tyle powinien pojsc f2
	auto res = f2 - f;
	//a o tyle f1
	auto res2 = f - f2;
	int x = 0;
	x--;
	return 0;
}