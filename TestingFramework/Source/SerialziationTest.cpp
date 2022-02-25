#include "SerialziationTest.h"
#include <fstream>
#include "json.hpp"
#include "CommonHeaders.h"
namespace Test{
	SerialziationTest::SerialziationTest(std::string rootpath):_rootpath(rootpath){}
	void SerialziationTest::PrepareTest(){
		//create default json files here
		auto fullpath = _rootpath + "engine.json";
		std::ofstream file(fullpath,std::ostream::out|std::ostream::app);
		if(file.good()){
			json engine = _enginesettings.JSerialize();
			file << engine.dump(4);
			file.close();
		}
		else{
			throw std::invalid_argument("Wrong path");
		}
	}
	bool SerialziationTest::RunTest(){
		PrepareTest();
		return true;
	}
}