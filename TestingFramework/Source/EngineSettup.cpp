#include "EngineSettup.h"
namespace Test {
	void EngineSettup::PrepareTest(){
		_engine.Main();
	}
	bool EngineSettup::RunTest(){
		try {
			PrepareTest();
			return true;
		}
		catch (...) {
			return false;
		}
	}
}