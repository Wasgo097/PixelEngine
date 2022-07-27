#include "ForestTest.h"
#include "PXFactory/SettingsFactory.h"
namespace Test {
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