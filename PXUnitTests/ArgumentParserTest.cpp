#include "pch.h"
#include <gtest/gtest.h>
#include "PXUtilities/ArgumentParser.h"
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
TEST_F(ArgumentParserTest, InputExistedKey) {
	EXPECT_FALSE(_parser->AddNewArgument("-arg1", "1"));
}
TEST_F(ArgumentParserTest, InputNewKey) {
	EXPECT_TRUE(_parser->AddNewArgument("-arg4", "1"));
}
TEST_F(ArgumentParserTest, GetWrongKeyTest) {
	auto val = _parser->GetRowValue("-arg4");
	EXPECT_EQ(val, std::nullopt);
}
TEST_F(ArgumentParserTest, GetExistedKeyRow) {
	EXPECT_STREQ(_parser->GetRowValue("-arg1")->c_str(), "0");
	EXPECT_STREQ(_parser->GetRowValue("-arg2")->c_str(), "val");
	EXPECT_STREQ(_parser->GetRowValue("-arg3")->c_str(), "true");
}
TEST_F(ArgumentParserTest, GetExistedKeyT) {
	EXPECT_EQ(_parser->GetValue<int>("-arg1"),0);
	EXPECT_TRUE(_parser->GetValue<bool>("-arg3"));
}
