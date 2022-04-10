#include "SerialziationTest.h"
#include "EngineSetup.h"
#include <iostream>
using namespace Test;
int main(){
	/*SerialziationTest test1("D:\\PixelEngine\\TestingFramework\\output\\");
	std::cout << "Serialization test result: " << test1.RunTest() << std::endl;*/
	EngineSetup test2;
	std::cout << "Engine settup test result: " << test2.RunTest() << std::endl;
	return 0;
}