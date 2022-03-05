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
		catch (...) {
			return false;
		}
	}
}