
#include "EngineSetupTest.h"
namespace Test {
	bool EngineSetupTest::PrepareTest(){
		return _engine.Run()==1;
	}
	bool EngineSetupTest::RunTest(){
		try {
			if (PrepareTest())
				return true;
			return false;
		}
		catch (std::exception& ex) {
			std::cout << "std exc " << ex.what() << "\n";
		}
		catch (...) {
			return false;
		}
		return false;
	}
}