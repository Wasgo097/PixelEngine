#include "pch.h"
#include <gtest/gtest.h>
#include "PXArgumentParser/ArgumentParser.h"
class ArgumentParserTest :public testing::Test {
public:
	virtual void SetUp()override {
		Reset();
	}
	void Reset() {
		_parser.reset(new ArgumentParser());
		_parser->AddNewArgument("-arg1", "0");
		_parser->AddNewArgument("-arg2", "val");
		_parser->AddNewArgument("-arg3", "true");
	}
protected:
	std::unique_ptr<ArgumentParser> _parser;
};
TEST_F(ArgumentParserTest, InputExistedKeyTest) {
	EXPECT_FALSE(_parser->AddNewArgument("-arg1", "1"));
}
TEST_F(ArgumentParserTest, InputNewKeyTest) {
	EXPECT_TRUE(_parser->AddNewArgument("-arg4", "1"));
}
TEST_F(ArgumentParserTest, GetWrongKeyTest) {
	auto val = _parser->GetRowValue("-arg4");
	EXPECT_EQ(val, std::nullopt);
}
TEST_F(ArgumentParserTest, GetExistedKeyRowTest) {
	EXPECT_STREQ(_parser->GetRowValue("-arg1")->c_str(), "0");
	EXPECT_STREQ(_parser->GetRowValue("-arg2")->c_str(), "val");
	EXPECT_STREQ(_parser->GetRowValue("-arg3")->c_str(), "true");
}
TEST_F(ArgumentParserTest, GetExistedKeyTTest) {
	EXPECT_EQ(*_parser->GetValue<int>("-arg1"), 0);
	EXPECT_TRUE(*_parser->GetValue<bool>("-arg3"));
}
TEST_F(ArgumentParserTest, InputAndGetTTest) {
	_parser->AddNewArgument("-arg4", "false");
	EXPECT_FALSE(*_parser->GetValue<bool>("-arg4"));
}
TEST_F(ArgumentParserTest, ConstructParserFromInvalidMainArgumentsTest) {
	bool is_exception = false;
	const char* argv[1];
	argv[0] = "test";
	try {
		_parser.reset(new ArgumentParser(1, argv));
	}
	catch (const std::invalid_argument&) {
		is_exception = true;
	}
	catch (const std::exception& ex) {
		std::cerr << "Exception massage " << ex.what() << std::endl;
	}
	EXPECT_TRUE(is_exception);
}
TEST_F(ArgumentParserTest, ConstructParserFromIncompleteMainArgumentsTest) {
	bool is_exception = false;
	const char* argv[4];
	argv[0] = "test";
	argv[1] = "-arg1";
	argv[2] = "true";
	argv[3] = "-arg2";
	try {
		_parser.reset(new ArgumentParser(4, argv));
	}
	catch (const std::invalid_argument&) {
		is_exception = true;
	}
	catch (const std::exception& ex) {
		std::cerr << "Exception massage " << ex.what() << std::endl;
	}
	EXPECT_TRUE(is_exception);
}
TEST_F(ArgumentParserTest, ConstructParserFromValidMainArgumentsTest) {
	const char* argv[5];
	argv[0] = "test";
	argv[1] = "-arg1";
	argv[2] = "true";
	argv[3] = "-arg2";
	argv[4] = "100";
	_parser.reset(new ArgumentParser(5, argv));
	EXPECT_TRUE(_parser->GetValue<bool>("-arg1"));
	EXPECT_EQ(_parser->GetValue<int>("-arg2"), 100);
}
