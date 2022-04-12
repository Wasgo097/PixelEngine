#include "Tests/SerializationTest/SerialziationTest.h"
#include "Tests/EngineSettup/EngineSetup.h"
#include <iostream>
using namespace Test;
int main(){
	SerialziationTest test1("cfg\\");
	//std::cout << "Serialization test result: " << test1.RunTest() << std::endl;
	EngineSetup test2;
	std::cout << "Engine settup test result: " << test2.RunTest() << std::endl;
	return 0;
}