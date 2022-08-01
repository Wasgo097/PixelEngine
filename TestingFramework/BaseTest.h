#pragma once
#include <iostream>
#include "PXUtilities/ArgumentParser.h"
namespace Test{
	class BaseTest{
	public:
		virtual bool PrepareTest() = 0;
		virtual bool RunTest() = 0;
	protected:
		BaseTest(const ArgumentParser& parser) :_parser{ parser } {}
		const ArgumentParser& _parser;
	};
}