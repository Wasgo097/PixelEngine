#include "EngineSetup.h"
namespace Test {
	EngineSetup::EngineSetup(){
	}
	void EngineSetup::PrepareTest(){
		_engine.Main();
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
	}
}