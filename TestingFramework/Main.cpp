#include "SerialziationTest.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace Test;
int main(){
	SerialziationTest test1("D:\\PixelEngine\\TestingFramework\\output\\");
	std::cout << "Serialization test result: " << test1.RunTest() << std::endl;
	return 0;
}