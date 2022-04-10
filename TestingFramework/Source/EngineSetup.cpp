#include "EngineSetup.h"
namespace Test {
	EngineSetup::EngineSetup() :_engine({}) {
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