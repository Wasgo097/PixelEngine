#include "PXArgumentParser/ArgumentParser.h"
#include "Tests/EngineSettup/EngineSetupTest.h"
#include "Tests/ActorAnimation/ActorAnimationTest.h"
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
	//EngineSetupTest engine_setup(parser);
	//std::cout << "Engine setup test result: \n" << engine_setup.RunTest() << std::endl;
	//ActorAnimationTest actor_animation(parser);
	//std::cout << "Animation test result: \n" << actor_animation.RunTest() << std::endl;
	//BlockEvent block_event(parser);
	//std::cout << "BlockEventTest result: \n" << block_event.RunTest() << std::endl;
	/*LoginExample login(parser);
	std::cout << "LoginExample result: \n" << login.RunTest() << std::endl;*/
	//MultipleWidgetsTest multiple_widget(parser);
	//std::cout << "MultipleWidgetsTest result: \n" << multiple_widget.RunTest() << std::endl;
	//PopUp pop_up(parser);
	//std::cout << "PopUp result: \n" << pop_up.RunTest() << std::endl;
	/*ScrollablePanel scrollable_panel(parser);
	std::cout << "ScrollablePanel result: \n" << scrollable_panel.RunTest() << std::endl;*/
	MainMenuTest main_menu(parser);
	std::cout << "MainMenuTest result: \n" << main_menu.RunTest() << std::endl;
	//Particle2Test particle2(parser);
	//std::cout << "Particle2Test result: \n" << particle2.RunTest() << std::endl;
	return 0;
}