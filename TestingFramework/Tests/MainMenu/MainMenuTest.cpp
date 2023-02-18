#include "MainMenuTest.h"

Test::MainMenuTest::MainMenuTest(const ArgumentParser& parser) :BaseTest(parser), _engine{_parser} {
}

bool Test::MainMenuTest::PrepareTest() {
	return _engine.Run() == 0;
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
