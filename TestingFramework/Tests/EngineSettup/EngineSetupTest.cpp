
#include "EngineSetupTest.h"
namespace Test {
	EngineSetupTest::EngineSetupTest(const ArgumentParser& parser) :BaseTest(parser)
	{
	}
	bool EngineSetupTest::PrepareTest(){
		return _engine.Run()==0;
	}
	bool EngineSetupTest::RunTest(){
		try {
			if (PrepareTest())
				return true;
			return false;
		}
		catch (std::exception& ex) {
			std::cerr << "EngineSetupTest exception " << ex.what() << "\n";
		}
		return false;
	}
}