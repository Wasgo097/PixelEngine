#include "PXArgumentParser/ArgumentParser.h"
#include "Tests/EngineSettup/EngineSetupTest.h"
#include "Tests/ActorAnimation/ActorAnimationTest.h"
#include "Tests/Forest/ForestTest.h"
#include "Tests/GUISettup/BlockEvent.h"
#include "Tests/GUISettup/LoginExample.h"
#include "Tests/GUISettup/MultipleWidgetsTest.h"
#include "Tests/GUISettup/PopUp.h"
#include "Tests/GUISettup/ScrollablePanel.h"
#include "Tests/GUISettup/Tabs.h"
#include "Tests/MainMenu/MainMenuTest.h"
#include "Tests/ExampleParticle2/Particle2Test.h"
using namespace Test;
int main(int argc, const char* argv[]) {
	ArgumentParser parser(argc, argv);
	//EngineSetupTest engineSetup(parser);
	//std::cout << "Engine setup test result: \n" << engineSetup.RunTest() << std::endl;
	//ActorAnimationTest actorAnimation(parser);
	//std::cout << "Animation test result: \n" << actorAnimation.RunTest() << std::endl;
	//ForestTest forest(parser);
	//std::cout << "Forest test result: \n" << forest.RunTest() << std::endl;
	BlockEvent blockEvent(parser);
	std::cout << "BlockEventTest result: \n" << blockEvent.RunTest() << std::endl;
	LoginExample login(parser);
	std::cout << "LoginExample result: \n" << login.RunTest() << std::endl;
	MultipleWidgetsTest multipleWidget(parser);
	std::cout << "MultipleWidgetsTest result: \n" << multipleWidget.RunTest() << std::endl;
	PopUp popUp(parser);
	std::cout << "PopUp result: \n" << popUp.RunTest() << std::endl;
	ScrollablePanel scrollablePanel(parser);
	std::cout << "ScrollablePanel result: \n" << scrollablePanel.RunTest() << std::endl;
	/*MainMenuTest mainMenu(parser);
	std::cout << "MainMenuTest result: \n" << mainMenu.RunTest() << std::endl;*/
	/*Particle2Test particle2(parser);
	std::cout << "Particle2Test result: \n" << particle2.RunTest() << std::endl;*/
	return 0;
}