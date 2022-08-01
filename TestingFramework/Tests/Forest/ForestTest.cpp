#include "ForestTest.h"
#include "PXFactory/SettingsFactory.h"
namespace Test {
	ForestTest::ForestTest(const ArgumentParser& parser) :BaseTest(parser) {
	}
	bool ForestTest::PrepareTest() {
		return _engine.Run() == 1;
	}
	bool ForestTest::RunTest() {
		try {
			if (PrepareTest())
				return true;
			return false;
		}
		catch (std::exception& ex) {
			std::cerr << "ForestTest exception " << ex.what() << "\n";
		}
		return false;
	}
}