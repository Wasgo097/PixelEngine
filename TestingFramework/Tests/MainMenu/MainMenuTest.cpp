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
		std::cerr << "MainMenuTest exception " << ex.what() << "\n";
	}
	return false;
}
