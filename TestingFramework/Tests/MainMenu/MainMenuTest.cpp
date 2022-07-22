#include "MainMenuTest.h"

bool Test::MainMenuTest::PrepareTest() {
	return _engine.Run() == 1;
}

bool Test::MainMenuTest::RunTest() {
	try {
		if (PrepareTest())
			return true;
		return false;
	}
	catch (std::exception& ex) {
		std::cout << "std exc " << ex.what() << "\n";
	}
	return false;
}
