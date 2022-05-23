
#include "EngineSetup.h"
namespace Test {
	void EngineSetup::PrepareTest(){
		int result=_engine.Run();
	}
	bool EngineSetup::RunTest(){
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