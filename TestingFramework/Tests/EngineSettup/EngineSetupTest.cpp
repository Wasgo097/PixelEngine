
#include "EngineSetupTest.h"
namespace Test {
	void EngineSetupTest::PrepareTest(){
		int result=_engine.Run();
	}
	bool EngineSetupTest::RunTest(){
		try {
			PrepareTest();
			return true;
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