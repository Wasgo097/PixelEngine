//#include "Tests/SerializationTest/SerialziationTest.h"
//#include "Tests/EngineSettup/EngineSetup.h"
#include "Tests/ActorAnimation/ActorAnimationTest.h"
#include <iostream>
using namespace Test;
int main(){
	/*SerialziationTest test1("cfg\\");
	std::cout << "Serialization test result: \n" << test1.RunTest() << std::endl;*/
	/*EngineSetup test2;
	std::cout << "Engine setup test result: \n" << test2.RunTest() << std::endl;*/

	ActorAnimationTest test3;
	std::cout << "Animation test result: \n" << test3.RunTest() << std::endl;
	return 0;
}